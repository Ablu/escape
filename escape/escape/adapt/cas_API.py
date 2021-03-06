# Copyright 2017 Janos Czentye
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at:
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""
Implements the platform and POX dependent logic for the Controller Adaptation
Sublayer.
"""
from escape.adapt import LAYER_NAME
from escape.adapt import log as log  # Adaptation layer logger
from escape.adapt.adaptation import ControllerAdapter, \
  InstallationFinishedEvent, \
  InfoRequestFinishedEvent
from escape.adapt.virtualization import GlobalViewVirtualizer
from escape.api.rest_API import RESTAPIManager
from escape.infr import LAYER_NAME as INFR_LAYER_NAME
from escape.nffg_lib.nffg import NFFG
from escape.util.api import AbstractAPI, RequestScheduler
from escape.util.config import CONFIG
from escape.util.misc import schedule_as_coop_task, quit_with_error
from escape.util.stat import stats
from pox.lib.revent.revent import Event


class GlobalResInfoEvent(Event):
  """
  Event for sending back requested Global Resource View.
  """

  def __init__ (self, dov):
    """
    Init.

    :param dov: Domain Virtualizer which handles the Global Infrastructure View.
    :type dov: :any:`DomainVirtualizer`
    :return: None
    """
    super(GlobalResInfoEvent, self).__init__()
    self.dov = dov


class DeployNFFGEvent(Event):
  """
  Event for passing mapped :class:`NFFG` to internally emulated network based on
  Mininet for testing.
  """

  def __init__ (self, nffg_part):
    """
    Init.

    :param nffg_part: NFFG needs to deploy
    :type nffg_part: :class:`NFFG`
    :return: None
    """
    super(DeployNFFGEvent, self).__init__()
    self.nffg_part = nffg_part


class ControllerAdaptationAPI(AbstractAPI):
  """
  Entry point for Controller Adaptation Sublayer (CAS).

  Maintain the contact with other UNIFY layers.

  Implement the Or - Ca reference point.
  """
  # Define specific name for core object i.e. pox.core.<_core_name>
  _core_name = LAYER_NAME
  # Events raised by this class
  _eventMixin_events = {GlobalResInfoEvent, InstallationFinishedEvent,
                        DeployNFFGEvent, InfoRequestFinishedEvent}

  # Dependencies
  dependencies = ('REST-API',)

  def __init__ (self, standalone=False, **kwargs):
    """
    .. seealso::
      :func:`AbstractAPI.__init__() <escape.util.api.AbstractAPI.__init__>`
    """
    log.info("Starting Controller Adaptation Sublayer...")
    # Set Infrastructure as a dependency
    if kwargs['with_infr']:
      log.debug("Set Infrastructure Layer as a dependency")
      self.dependencies = self.dependencies + (INFR_LAYER_NAME,)
    # Mandatory super() call
    self.controller_adapter = None
    self.api_mgr = RESTAPIManager(unique_bb_id=False,
                                  unique_nf_id=True,
                                  logger=log)
    super(ControllerAdaptationAPI, self).__init__(standalone, **kwargs)

  def initialize (self):
    """
    .. seealso::
      :func:`AbstractAPI.initialize() <escape.util.api.AbstractAPI.initialize>`
    """
    log.debug("Initializing Controller Adaptation Sublayer...")
    self.controller_adapter = ControllerAdapter(self, with_infr=self._with_infr)
    if self._mapped_nffg:
      try:
        mapped_request = self._read_data_from_file(self._mapped_nffg)
        mapped_request = NFFG.parse(mapped_request)
        self.__proceed_installation(mapped_nffg=mapped_request)
      except (ValueError, IOError, TypeError) as e:
        log.error("Can't load service request from file because of: " + str(e))
        quit_with_error(msg=str(e), logger=log)
      else:
        log.debug("Graph representation is loaded successfully!")
    if self._dovapi:
      self._initialize_dov_api()
    log.info("Controller Adaptation Sublayer has been initialized!")

  def shutdown (self, event):
    """
    .. seealso::
      :func:`AbstractAPI.shutdown() <escape.util.api.AbstractAPI.shutdown>`

    :param event: event object
    :type: :class:`pox.lib.revent.revent.Event`
    :return: None
    """
    log.info("Controller Adaptation Sublayer is going down...")
    self.controller_adapter.shutdown()

  def _initialize_dov_api (self):
    rest_api = self.get_dependent_component('REST-API')
    rest_api.register_component(component=self)
    dov = self.controller_adapter.DoVManager.dov
    self.dov_api_view = GlobalViewVirtualizer(id=self._core_name,
                                              global_view=dov)
    log.debug("Created default Virtualizer View for DOV-API: %s"
              % self.dov_api_view)
    return

  ##############################################################################
  # UNIFY Or - Ca API functions starts here
  ##############################################################################

  def _handle_InstallNFFGEvent (self, event):
    """
    Install mapped NF-FG (UNIFY Or - Ca API).

    :param event: event object contains mapped NF-FG
    :type event: :any:`InstallNFFGEvent`
    :return: None
    """
    log.getChild('API').info("Received mapped NF-FG: %s from %s Layer" % (
      event.mapped_nffg, str(event.source._core_name).title()))
    self.__proceed_installation(mapped_nffg=event.mapped_nffg,
                                original_request=event.original_request)

  @schedule_as_coop_task
  def __proceed_installation (self, mapped_nffg, original_request=None,
                              direct_deploy=False):
    """
    Helper function to instantiate the NFFG mapping from different source.

    :param mapped_nffg: pre-mapped service request
    :type mapped_nffg: :class:`NFFG`
    :return: None
    """
    log.getChild('API').info("Invoke install_nffg on %s with NF-FG: %s " % (
      self.__class__.__name__, mapped_nffg))
    stats.add_measurement_start_entry(type=stats.TYPE_DEPLOY,
                                      info=LAYER_NAME)
    try:
      deploy_status = self.controller_adapter.install_nffg(
        mapped_nffg=mapped_nffg,
        original_request=original_request,
        direct_deploy=direct_deploy)
    except Exception as e:
      log.error("Something went wrong during NFFG installation: %s" % e)
      self._process_mapping_result(nffg_id=mapped_nffg.id, fail=True)
      self.raiseEventNoErrors(InstallationFinishedEvent,
                              id=mapped_nffg.id,
                              result=InstallationFinishedEvent.DEPLOY_ERROR)
      return
    log.getChild('API').debug("Invoked install_nffg on %s is finished!" %
                              self.__class__.__name__)
    if deploy_status is None:
      log.error("Deploy status is missing!")
      self._process_mapping_result(nffg_id=mapped_nffg.id, fail=True)
      self.raiseEventNoErrors(InstallationFinishedEvent,
                              id=mapped_nffg.id,
                              result=InstallationFinishedEvent.DEPLOY_ERROR)
    elif not deploy_status.still_pending:
      result = InstallationFinishedEvent.get_result_from_status(deploy_status)
      log.info("Overall installation result: %s" % result)
      is_fail = InstallationFinishedEvent.is_error(result)
      self._process_mapping_result(nffg_id=mapped_nffg.id, fail=is_fail)
      self.raiseEventNoErrors(InstallationFinishedEvent,
                              id=mapped_nffg.id, result=result)
    elif deploy_status.standby:
      if self._dovapi:
        RequestScheduler().set_orchestration_standby()

  def _process_mapping_result (self, nffg_id, fail):
    """

    :param nffg_id:
    :param fail:
    :return:
    """
    log.getChild('API').debug("Cache request status...")
    req_status = self.api_mgr.request_cache.get_request_by_nffg_id(nffg_id)
    if req_status is None:
      log.getChild('API').debug("Request status is missing for NFFG: %s! "
                                "Skip result processing..." % nffg_id)
      return
    log.getChild('API').debug("Process mapping result...")
    message_id = req_status.message_id
    if message_id is not None:
      if fail:
        self.api_mgr.request_cache.set_error_result(id=message_id)
      else:
        self.api_mgr.request_cache.set_success_result(id=message_id)
      log.info("Set request status: %s for message: %s"
               % (req_status.status, req_status.message_id))
      ret = self.api_mgr.invoke_callback(message_id=message_id)
      if ret is None:
        log.getChild('API').debug("No callback was defined!")
      else:
        log.getChild('API').debug(
          "Callback: %s has invoked with return value: %s" % (
            req_status.get_callback(), ret))
    RequestScheduler().set_orchestration_finished(id=nffg_id)

  @schedule_as_coop_task
  def _handle_CollectMonitoringDataEvent (self, event):
    """
    Propagate Info request to the domain.

    :param event: event object
    :type event: :class:`CollectMonitoringDataEvent`
    :return: None
    """
    log.getChild('API').info("Received recursive monitoring request from %s "
                             "Layer" % event.source._core_name.title())
    try:
      status = self.controller_adapter.propagate_info_requests(id=event.id,
                                                               info=event.info)
    except Exception:
      log.exception("Something went wrong during info request processing!")
      self.raiseEventNoErrors(InfoRequestFinishedEvent,
                              result=InfoRequestFinishedEvent.ERROR)
      return
    log.getChild('API').debug("Invoked 'info' on %s is finished!" %
                              self.__class__.__name__)
    if not status.still_pending:
      result = InfoRequestFinishedEvent.get_result_from_status(status)
      self.raiseEventNoErrors(InfoRequestFinishedEvent,
                              result=result,
                              status=status)

  ##############################################################################
  # UNIFY ( Ca - ) Co - Rm API functions starts here
  ##############################################################################

  def _handle_GetGlobalResInfoEvent (self, event):
    """
    Generate global resource info and send back to ROS.

    :param event: event object
    :type event: :class:`GetGlobalResInfoEvent`
    :return: None
    """
    log.getChild('API').debug(
      "Received DoV request from %s layer" % str(
        event.source._core_name).title())
    # Currently global view is a reference to the DoV to keep ESCAPE fast
    dov = self.controller_adapter.DoVManager.dov
    log.getChild('API').debug("Sending back DoV: %s..." % dov)
    self.raiseEventNoErrors(GlobalResInfoEvent, dov)

  ##############################################################################
  # Agent API functions starts here
  ##############################################################################

  def rest_api_get_config (self):
    """
    Implementation of REST-API RPC: get-config. Return with the global
    resource as an :class:`NFFG` if it has been changed otherwise return with
    False.

    :return: global resource view (DoV)
    :rtype: :class:`NFFG` or False
    """
    # return self.controller_adapter.DoVManager.dov.get_resource_info()
    log.getChild('[DOV-API]').debug("Requesting Virtualizer for DoV-API")
    if self.dov_api_view is not None:
      # Check the topology is initialized
      if self.dov_api_view.revision is None:
        log.getChild('[DOV-API]').debug("DoV has not initialized yet! "
                                        "Force to get default topology...")
      else:
        # Check if the resource is changed
        if self.api_mgr.topology_revision == self.dov_api_view.revision:
          # If resource has not been changed return False
          # This causes to response with the cached topology
          log.debug("Global resource has not changed (revision: %s)! "
                    % self.dov_api_view.revision)
          log.debug("Send topology from cache...")
          if self.api_mgr.last_response is None:
            log.error("Cached topology is missing!")
            return
          else:
            return self.api_mgr.last_response
        else:
          log.getChild('[DOV-API]').debug("Response cache is outdated "
                                          "(new revision: %s)!"
                                          % self.dov_api_view.revision)
      res = self.dov_api_view.get_resource_info()
      self.api_mgr.topology_revision = self.dov_api_view.revision
      log.debug("Updated revision number: %s"
                % self.api_mgr.topology_revision)
      if CONFIG.get_rest_api_config(self._core_name)['unify_interface']:
        log.info("Convert internal NFFG to Virtualizer...")
        res = self.api_mgr.converter.dump_to_Virtualizer(nffg=res)
      log.debug("Cache acquired topology...")
      self.api_mgr.last_response = res
      return res
    else:
      log.error("Virtualizer(id=%s) assigned to DoV-API is not found!" %
                self._core_name)

  # noinspection PyUnusedLocal
  def rest_api_edit_config (self, id, data, params=None):
    """
    Implement edit-config call for CAS layer. Receive edit-config request from
    external component and directly forward data for deployment.

    :param params: request params
    :type params: dict
    :return: None
    """
    log.getChild('[DOV-API]').info("Invoke instantiation on %s with NF-FG: "
                                   "%s " % (self.__class__.__name__, id))
    if CONFIG.get_rest_api_config(self._core_name)['unify_interface']:
      log.debug("Virtualizer format enabled! Start conversion step...")
      if CONFIG.get_rest_api_config(self._core_name)['diff']:
        log.debug("Diff format enabled! Start patching step...")
        if self.api_mgr.last_response is None:
          log.info("Missing cached Virtualizer! Acquiring topology now...")
          self.rest_api_get_config()
        stats.add_measurement_start_entry(type=stats.TYPE_PROCESSING,
                                          info="RECREATE-FULL-REQUEST")
        log.info("Patching cached topology with received diff...")
        full_req = self.api_mgr.last_response.yang_copy()
        full_req.patch(source=data)
        stats.add_measurement_end_entry(type=stats.TYPE_PROCESSING,
                                        info="RECREATE-FULL-REQUEST")
      else:
        full_req = data
      log.info("Converting full request data...")
      stats.add_measurement_start_entry(type=stats.TYPE_CONVERSION,
                                        info="VIRTUALIZER-->NFFG")
      nffg = self.api_mgr.converter.parse_from_Virtualizer(vdata=full_req)
      stats.add_measurement_end_entry(type=stats.TYPE_CONVERSION,
                                      info="VIRTUALIZER-->NFFG")
    else:
      nffg = data
    log.debug("Set NFFG id: %s" % id)
    if nffg.service_id is None:
      nffg.service_id = nffg.id
    nffg.id = id
    if params:
      nffg.add_metadata(name="params", value=params)
    log.info("Proceeding request: %s to instantiation..." % id)
    if CONFIG.get_vnfm_enabled():
      deploy_status = self.controller_adapter.status_mgr.get_last_status()
      if deploy_status is None:
        log.warning("Received direct DoV rewrite request from external "
                    "component without any preliminary deploy request!")
      else:
        if deploy_status.id != nffg.id:
          log.error("Received direct deploy request id: %s is different from "
                    "service request under deploy: %s" % (nffg.id,
                                                          deploy_status.id))
          return
        else:
          self.controller_adapter.cancel_vnfm_timer()
    log.getChild('API').debug("Store received DoV request...")
    msg_id = self.api_mgr.request_cache.cache_request_by_nffg(nffg=nffg)
    if msg_id is not None:
      self.api_mgr.request_cache.set_in_progress(id=msg_id)
      log.getChild('API').debug("Request is stored with id: %s" % msg_id)
    else:
      log.getChild('API').warning("No request info detected.")
    self.__proceed_installation(mapped_nffg=nffg, direct_deploy=True)

# class DirectDoVRequestHandler(BasicUnifyRequestHandler):
#   """
#   Dedicated request handler class for CAS REST-API.
#   """
#   LOGGER_NAME = "Dov-API"
#   log = log.getChild("[%s]" % LOGGER_NAME)
#   # Name mapper to avoid Python naming constraint
#   rpc_mapper = {
#     'get-config': "get_config",
#     'edit-config': "edit_config"
#   }
#   """Name mapper to avoid Python naming constraint"""
#   # Bound function
#   API_CALL_RESOURCE = 'api_cas_get_config'
#   API_CALL_REQUEST = 'api_cas_edit_config'
#
#   def setup (self):
#     super(DirectDoVRequestHandler, self).setup()
#     self.converter = NFFGConverter(unique_bb_id=False,
#                                    unique_nf_id=True,
#                                    logger=log)
#     # Force disable adding domain to BB nodes that are parts of DoV
#     self.converter._unique_bb_id = False
#     # Force enable adding domain to BB nodes that are parts of DoV
#     self.converter._unique_nf_id = True
#     self.log.debug("Forced ID management for %s: unique BiSBiS ID: %s,"
#                    " unique NF ID: %s" % (self.__class__.__name__,
#                                           self.converter._unique_bb_id,
#                                           self.converter._unique_nf_id))

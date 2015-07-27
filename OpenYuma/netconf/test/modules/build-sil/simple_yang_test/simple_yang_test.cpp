
/* 

 * Copyright (c) 2009 - 2011, Andy Bierman
 * All Rights Reserved.
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *

*** Generated by yangdump 2.1.1630

    Combined SIL module
    module simple_yang_test
    revision 2011-11-21
    namespace http://netconfcentral.org/ns/simple_yang_test

 */

extern "C" {
#include <xmlstring.h>

#include "procdefs.h"
#include "agt.h"
#include "agt_cb.h"
#include "agt_timer.h"
#include "agt_util.h"
#include "dlq.h"
#include "ncx.h"
#include "ncxmod.h"
#include "ncxtypes.h"
#include "status.h"
#include "simple_yang_test.h"
}

#include "test/support/callbacks/sil-callback-log.h"

/* module static variables */
static ncx_module_t *simple_yang_test_mod;
static obj_template_t *protocol_obj;
static obj_template_t *interface_obj;
static val_value_t *protocol_val;
static val_value_t *interface_val;

/* put your static variables here */


/********************************************************************
* FUNCTION y_simple_yang_test_init_static_vars
* 
* initialize module static variables
* 
********************************************************************/
static void y_simple_yang_test_init_static_vars (void)
{
    simple_yang_test_mod = NULL;
    protocol_obj = NULL;
    interface_obj = NULL;
    protocol_val = NULL;
    interface_val = NULL;

    /* init your static variables here */

} /* y_simple_yang_test_init_static_vars */


/********************************************************************
* FUNCTION simple_yang_test_protocol_name_udp_udp_edit
* 
* Edit database object callback
* Path: /protocol/name/udp/udp
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t simple_yang_test_protocol_name_udp_udp_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter simple_yang_test_protocol_name_udp_udp_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    YumaTest::SILCallbackLog& cbLog = YumaTest::SILCallbackLog::getInstance();
    YumaTest::SILCallbackLog::CallbackInfo cbData;
    cbData.cbName = "simple_yang_test_protocol_name_udp_udp_edit";
    val_value_t* value = (newval) ? newval : curval;
    std::string module_name = (char*) val_get_mod_name(value);

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        cbData.cbType = "validate";
        cbLog.addCallback(module_name, cbData);
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        cbData.cbType = "apply";
        cbLog.addCallback(module_name, cbData);
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
        cbData.cbType = "commit";
        /* device instrumentation done here */
        switch (editop) {
        case OP_EDITOP_LOAD:
            cbData.cbPhase = "load";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_MERGE:
            cbData.cbPhase = "merge";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_REPLACE:
            cbData.cbPhase = "replace";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_CREATE:
            cbData.cbPhase = "create";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_DELETE:
            cbData.cbPhase = "delete";
            cbLog.addCallback(module_name, cbData);
            break;
        default:
            cbData.cbPhase = "default";
            cbLog.addCallback(module_name, cbData);
            res = SET_ERROR(ERR_INTERNAL_VAL);
        }
        break;
    case AGT_CB_ROLLBACK:
        cbData.cbType = "rollback";
        cbLog.addCallback(module_name, cbData);
        /* undo device instrumentation here */
        break;
    default:
        cbData.cbType = "default";
        cbLog.addCallback(module_name, cbData);
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* simple_yang_test_protocol_name_udp_udp_edit */


/********************************************************************
* FUNCTION simple_yang_test_protocol_name_tcp_tcp_edit
* 
* Edit database object callback
* Path: /protocol/name/tcp/tcp
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t simple_yang_test_protocol_name_tcp_tcp_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter simple_yang_test_protocol_name_tcp_tcp_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    YumaTest::SILCallbackLog& cbLog = YumaTest::SILCallbackLog::getInstance();
    YumaTest::SILCallbackLog::CallbackInfo cbData;
    cbData.cbName = "simple_yang_test_protocol_name_tcp_tcp_edit";
    val_value_t* value = (newval) ? newval : curval;
    std::string module_name = (char*) val_get_mod_name(value);

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        cbData.cbType = "validate";
        cbLog.addCallback(module_name, cbData);
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        cbData.cbType = "apply";
        cbLog.addCallback(module_name, cbData);
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
        cbData.cbType = "commit";
        /* device instrumentation done here */
        switch (editop) {
        case OP_EDITOP_LOAD:
            cbData.cbPhase = "load";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_MERGE:
            cbData.cbPhase = "merge";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_REPLACE:
            cbData.cbPhase = "replace";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_CREATE:
            cbData.cbPhase = "create";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_DELETE:
            cbData.cbPhase = "delete";
            cbLog.addCallback(module_name, cbData);
            break;
        default:
            cbData.cbPhase = "default";
            cbLog.addCallback(module_name, cbData);
            res = SET_ERROR(ERR_INTERNAL_VAL);
        }
        break;
    case AGT_CB_ROLLBACK:
        cbData.cbType = "rollback";
        cbLog.addCallback(module_name, cbData);
        /* undo device instrumentation here */
        break;
    default:
        cbData.cbType = "default";
        cbLog.addCallback(module_name, cbData);
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* simple_yang_test_protocol_name_tcp_tcp_edit */


/********************************************************************
* FUNCTION simple_yang_test_protocol_edit
* 
* Edit database object callback
* Path: /protocol
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t simple_yang_test_protocol_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter simple_yang_test_protocol_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    YumaTest::SILCallbackLog& cbLog = YumaTest::SILCallbackLog::getInstance();
    YumaTest::SILCallbackLog::CallbackInfo cbData;
    cbData.cbName = "simple_yang_test_protocol_edit";
    val_value_t* value = (newval) ? newval : curval;
    std::string module_name = (char*) val_get_mod_name(value);

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        cbData.cbType = "validate";
        cbLog.addCallback(module_name, cbData);
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        cbData.cbType = "apply";
        cbLog.addCallback(module_name, cbData);
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
        cbData.cbType = "commit";
        /* device instrumentation done here */
        switch (editop) {
        case OP_EDITOP_LOAD:
            cbData.cbPhase = "load";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_MERGE:
            cbData.cbPhase = "merge";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_REPLACE:
            cbData.cbPhase = "replace";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_CREATE:
            cbData.cbPhase = "create";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_DELETE:
            cbData.cbPhase = "delete";
            cbLog.addCallback(module_name, cbData);
            break;
        default:
            cbData.cbPhase = "default";
            cbLog.addCallback(module_name, cbData);
            res = SET_ERROR(ERR_INTERNAL_VAL);
        }

        if (res == NO_ERR) {
            res = agt_check_cache(&protocol_val, newval, curval, editop);
        }
        
        break;
    case AGT_CB_ROLLBACK:
        cbData.cbType = "rollback";
        cbLog.addCallback(module_name, cbData);
        /* undo device instrumentation here */
        break;
    default:
        cbData.cbType = "default";
        cbLog.addCallback(module_name, cbData);
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* simple_yang_test_protocol_edit */


/********************************************************************
* FUNCTION simple_yang_test_interface_ifType_edit
* 
* Edit database object callback
* Path: /interface/ifType
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t simple_yang_test_interface_ifType_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter simple_yang_test_interface_ifType_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    YumaTest::SILCallbackLog& cbLog = YumaTest::SILCallbackLog::getInstance();
    YumaTest::SILCallbackLog::CallbackInfo cbData;
    cbData.cbName = "simple_yang_test_interface_ifType_edit";
    val_value_t* value = (newval) ? newval : curval;
    std::string module_name = (char*) val_get_mod_name(value);

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        cbData.cbType = "validate";
        cbLog.addCallback(module_name, cbData);
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        cbData.cbType = "apply";
        cbLog.addCallback(module_name, cbData);
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
        cbData.cbType = "commit";
        /* device instrumentation done here */
        switch (editop) {
        case OP_EDITOP_LOAD:
            cbData.cbPhase = "load";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_MERGE:
            cbData.cbPhase = "merge";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_REPLACE:
            cbData.cbPhase = "replace";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_CREATE:
            cbData.cbPhase = "create";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_DELETE:
            cbData.cbPhase = "delete";
            cbLog.addCallback(module_name, cbData);
            break;
        default:
            cbData.cbPhase = "default";
            cbLog.addCallback(module_name, cbData);
            res = SET_ERROR(ERR_INTERNAL_VAL);
        }
        break;
    case AGT_CB_ROLLBACK:
        cbData.cbType = "rollback";
        cbLog.addCallback(module_name, cbData);
        /* undo device instrumentation here */
        break;
    default:
        cbData.cbType = "default";
        cbLog.addCallback(module_name, cbData);
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* simple_yang_test_interface_ifType_edit */


/********************************************************************
* FUNCTION simple_yang_test_interface_ifMTU_edit
* 
* Edit database object callback
* Path: /interface/ifMTU
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t simple_yang_test_interface_ifMTU_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter simple_yang_test_interface_ifMTU_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    YumaTest::SILCallbackLog& cbLog = YumaTest::SILCallbackLog::getInstance();
    YumaTest::SILCallbackLog::CallbackInfo cbData;
    cbData.cbName = "simple_yang_test_interface_ifMTU_edit";
    val_value_t* value = (newval) ? newval : curval;
    std::string module_name = (char*) val_get_mod_name(value);

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        cbData.cbType = "validate";
        cbLog.addCallback(module_name, cbData);
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        cbData.cbType = "apply";
        cbLog.addCallback(module_name, cbData);
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
        cbData.cbType = "commit";
        /* device instrumentation done here */
        switch (editop) {
        case OP_EDITOP_LOAD:
            cbData.cbPhase = "load";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_MERGE:
            cbData.cbPhase = "merge";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_REPLACE:
            cbData.cbPhase = "replace";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_CREATE:
            cbData.cbPhase = "create";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_DELETE:
            cbData.cbPhase = "delete";
            cbLog.addCallback(module_name, cbData);
            break;
        default:
            cbData.cbPhase = "default";
            cbLog.addCallback(module_name, cbData);
            res = SET_ERROR(ERR_INTERNAL_VAL);
        }
        break;
    case AGT_CB_ROLLBACK:
        cbData.cbType = "rollback";
        cbLog.addCallback(module_name, cbData);
        /* undo device instrumentation here */
        break;
    default:
        cbData.cbType = "default";
        cbLog.addCallback(module_name, cbData);
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* simple_yang_test_interface_ifMTU_edit */


/********************************************************************
* FUNCTION simple_yang_test_interface_edit
* 
* Edit database object callback
* Path: /interface
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t simple_yang_test_interface_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter simple_yang_test_interface_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    YumaTest::SILCallbackLog& cbLog = YumaTest::SILCallbackLog::getInstance();
    YumaTest::SILCallbackLog::CallbackInfo cbData;
    cbData.cbName = "simple_yang_test_interface_edit";
    val_value_t* value = (newval) ? newval : curval;
    std::string module_name = (char*) val_get_mod_name(value);

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        cbData.cbType = "validate";
        cbLog.addCallback(module_name, cbData);
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        cbData.cbType = "apply";
        cbLog.addCallback(module_name, cbData);
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
        cbData.cbType = "commit";
        /* device instrumentation done here */
        switch (editop) {
        case OP_EDITOP_LOAD:
            cbData.cbPhase = "load";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_MERGE:
            cbData.cbPhase = "merge";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_REPLACE:
            cbData.cbPhase = "replace";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_CREATE:
            cbData.cbPhase = "create";
            cbLog.addCallback(module_name, cbData);
            break;
        case OP_EDITOP_DELETE:
            cbData.cbPhase = "delete";
            cbLog.addCallback(module_name, cbData);
            break;
        default:
            cbData.cbPhase = "default";
            cbLog.addCallback(module_name, cbData);
            res = SET_ERROR(ERR_INTERNAL_VAL);
        }

        if (res == NO_ERR) {
            res = agt_check_cache(&interface_val, newval, curval, editop);
        }
        
        break;
    case AGT_CB_ROLLBACK:
        cbData.cbType = "rollback";
        cbLog.addCallback(module_name, cbData);
        /* undo device instrumentation here */
        break;
    default:
        cbData.cbType = "default";
        cbLog.addCallback(module_name, cbData);
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* simple_yang_test_interface_edit */


/********************************************************************
* FUNCTION y_simple_yang_test_init
* 
* initialize the simple_yang_test server instrumentation library
* 
* INPUTS:
*    modname == requested module name
*    revision == requested version (NULL for any)
* 
* RETURNS:
*     error status
********************************************************************/
status_t y_simple_yang_test_init (
    const xmlChar *modname,
    const xmlChar *revision)
{
    status_t res = NO_ERR;
    agt_profile_t *agt_profile;

    y_simple_yang_test_init_static_vars();

    /* change if custom handling done */
    if (xml_strcmp(modname, y_simple_yang_test_M_simple_yang_test)) {
        return ERR_NCX_UNKNOWN_MODULE;
    }

    if (revision && xml_strcmp(revision, y_simple_yang_test_R_simple_yang_test)) {
        return ERR_NCX_WRONG_VERSION;
    }

    agt_profile = agt_get_profile();

    res = ncxmod_load_module(
        y_simple_yang_test_M_simple_yang_test,
        y_simple_yang_test_R_simple_yang_test,
        &agt_profile->agt_savedevQ,
        &simple_yang_test_mod);
    if (res != NO_ERR) {
        return res;
    }

    protocol_obj = ncx_find_object(
        simple_yang_test_mod,
        y_simple_yang_test_N_protocol);
    if (simple_yang_test_mod == NULL) {
        return SET_ERROR(ERR_NCX_DEF_NOT_FOUND);
    }
    
    interface_obj = ncx_find_object(
        simple_yang_test_mod,
        y_simple_yang_test_N_interface);
    if (simple_yang_test_mod == NULL) {
        return SET_ERROR(ERR_NCX_DEF_NOT_FOUND);
    }
    
    res = agt_cb_register_callback(
        y_simple_yang_test_M_simple_yang_test,
        (const xmlChar *)"/interface",
        (const xmlChar *)"2011-11-21",
        simple_yang_test_interface_edit);
    if (res != NO_ERR) {
        return res;
    }

    res = agt_cb_register_callback(
        y_simple_yang_test_M_simple_yang_test,
        (const xmlChar *)"/interface/ifMTU",
        (const xmlChar *)"2011-11-21",
        simple_yang_test_interface_ifMTU_edit);
    if (res != NO_ERR) {
        return res;
    }

    res = agt_cb_register_callback(
        y_simple_yang_test_M_simple_yang_test,
        (const xmlChar *)"/interface/ifType",
        (const xmlChar *)"2011-11-21",
        simple_yang_test_interface_ifType_edit);
    if (res != NO_ERR) {
        return res;
    }

    res = agt_cb_register_callback(
        y_simple_yang_test_M_simple_yang_test,
        (const xmlChar *)"/protocol",
        (const xmlChar *)"2011-11-21",
        simple_yang_test_protocol_edit);
    if (res != NO_ERR) {
        return res;
    }

    res = agt_cb_register_callback(
        y_simple_yang_test_M_simple_yang_test,
        (const xmlChar *)"/protocol/name/tcp/tcp",
        (const xmlChar *)"2011-11-21",
        simple_yang_test_protocol_name_tcp_tcp_edit);
    if (res != NO_ERR) {
        return res;
    }

    res = agt_cb_register_callback(
        y_simple_yang_test_M_simple_yang_test,
        (const xmlChar *)"/protocol/name/udp/udp",
        (const xmlChar *)"2011-11-21",
        simple_yang_test_protocol_name_udp_udp_edit);
    if (res != NO_ERR) {
        return res;
    }

    /* put your module initialization code here */
    
    return res;
} /* y_simple_yang_test_init */


/********************************************************************
* FUNCTION y_simple_yang_test_init2
* 
* SIL init phase 2: non-config data structures
* Called after running config is loaded
* 
* RETURNS:
*     error status
********************************************************************/
status_t y_simple_yang_test_init2 (void)
{
    status_t res = NO_ERR;

    interface_val = agt_init_cache(
        y_simple_yang_test_M_simple_yang_test,
        y_simple_yang_test_N_interface,
        &res);
    if (res != NO_ERR) {
        return res;
    }

    protocol_val = agt_init_cache(
        y_simple_yang_test_M_simple_yang_test,
        y_simple_yang_test_N_protocol,
        &res);
    if (res != NO_ERR) {
        return res;
    }

    /* put your init2 code here */

    return res;
} /* y_simple_yang_test_init2 */


/********************************************************************
* FUNCTION y_simple_yang_test_cleanup
*    cleanup the server instrumentation library
* 
********************************************************************/
void y_simple_yang_test_cleanup (void)
{
    agt_cb_unregister_callbacks(
        y_simple_yang_test_M_simple_yang_test,
        (const xmlChar *)"/interface");

    agt_cb_unregister_callbacks(
        y_simple_yang_test_M_simple_yang_test,
        (const xmlChar *)"/interface/ifMTU");

    agt_cb_unregister_callbacks(
        y_simple_yang_test_M_simple_yang_test,
        (const xmlChar *)"/interface/ifType");

    agt_cb_unregister_callbacks(
        y_simple_yang_test_M_simple_yang_test,
        (const xmlChar *)"/protocol");

    agt_cb_unregister_callbacks(
        y_simple_yang_test_M_simple_yang_test,
        (const xmlChar *)"/protocol/name/tcp/tcp");

    agt_cb_unregister_callbacks(
        y_simple_yang_test_M_simple_yang_test,
        (const xmlChar *)"/protocol/name/udp/udp");

    /* put your cleanup code here */
    
} /* y_simple_yang_test_cleanup */

/* END simple_yang_test.c */

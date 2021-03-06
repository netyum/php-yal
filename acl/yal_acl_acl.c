/*
  +----------------------------------------------------------------------+
  | Yet Another Framework                                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Jun Wen  <wenjun1055@gmail.com>                              |
  +----------------------------------------------------------------------+
*/
  
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend_API.h"
#include "zend_exceptions.h"
#include "Zend/zend_interfaces.h"

#include "php_yal.h"
#include "yal_acl_acl.h"
#include "yal_acl_acl_interface.h"
#include "yal_acl_role_registery.h"
#include "yal_acl_role_generic_role.h"
#include "yal_acl_role_role_interface.h"
#include "yal_acl_assertion_assertion_interface.h"
#include "yal_acl_resource_resource_interface.h"
#include "yal_acl_resource_generic_resource.h"

zend_class_entry *yal_acl_acl_ce;

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_add_role_arg, 0, 0, 1)
    //ZEND_ARG_OBJ_INFO(0, role, Yal\\Acl\\AclInterface, 0)
    ZEND_ARG_INFO(0, role)
    ZEND_ARG_INFO(0, parents)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_get_role_arg, 0, 0, 1)
    ZEND_ARG_INFO(0, role)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_has_role_arg, 0, 0, 1)
    ZEND_ARG_INFO(0, role)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_inherits_role_arg, 0, 0, 2)
    ZEND_ARG_INFO(0, role)
    ZEND_ARG_INFO(0, inherit)
    ZEND_ARG_INFO(0, onlyParents)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_remove_role_arg, 0, 0, 1)
    ZEND_ARG_INFO(0, role)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_add_resource_arg, 0, 0, 1)
    ZEND_ARG_INFO(0, resource)
    ZEND_ARG_INFO(0, parent)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_get_resource_arg, 0, 0, 1)
    ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_has_resource_arg, 0, 0, 1)
    ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_inherits_resource_arg, 0, 0, 2)
    ZEND_ARG_INFO(0, resource)
    ZEND_ARG_INFO(0, inherit)
    ZEND_ARG_INFO(0, onlyParents)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_remove_resource_arg, 0, 0, 1)
    ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_allow_arg, 0, 0, 0)
    ZEND_ARG_INFO(0, roles)
    ZEND_ARG_INFO(0, resources)
    ZEND_ARG_INFO(0, privileges)
    ZEND_ARG_OBJ_INFO(0, role, Yal\\Acl\\Assertion\\AssertionInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_deny_arg, 0, 0, 0)
    ZEND_ARG_INFO(0, roles)
    ZEND_ARG_INFO(0, resources)
    ZEND_ARG_INFO(0, privileges)
    ZEND_ARG_OBJ_INFO(0, role, Yal\\Acl\\Assertion\\AssertionInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_remove_allow_arg, 0, 0, 0)
    ZEND_ARG_INFO(0, roles)
    ZEND_ARG_INFO(0, resources)
    ZEND_ARG_INFO(0, privileges)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_remove_deny_arg, 0, 0, 0)
    ZEND_ARG_INFO(0, roles)
    ZEND_ARG_INFO(0, resources)
    ZEND_ARG_INFO(0, privileges)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_set_rule_arg, 0, 0, 2)
    ZEND_ARG_INFO(0, operation)
    ZEND_ARG_INFO(0, type)
    ZEND_ARG_INFO(0, roles)
    ZEND_ARG_INFO(0, resources)
    ZEND_ARG_INFO(0, privileges)
    ZEND_ARG_OBJ_INFO(0, role, Yal\\Acl\\Assertion\\AssertionInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_get_child_resources_arg, 0, 0, 1)
    ZEND_ARG_OBJ_INFO(0, resource, Yal\\Acl\\Resource\\ResourceInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(yal_acl_acl_is_allowed_arg, 0, 0, 0)
    ZEND_ARG_INFO(0, role)
    ZEND_ARG_INFO(0, resource)
    ZEND_ARG_INFO(0, privilege)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ yal_call_method
 * Only returns the returned zval if retval_ptr != NULL 
 */
ZEND_API zval* yal_call_method(zval **object_pp, zend_class_entry *obj_ce, 
                               zend_function **fn_proxy, char *function_name, 
                               int function_name_len, zval **retval_ptr_ptr, 
                               int param_count, zval* arg1, zval* arg2, zval* arg3 TSRMLS_DC)
{
    int result;
    zend_fcall_info fci;
    zval z_fname;
    zval *retval;
    HashTable *function_table;
    
    zval **params[3];
    params[0] = &arg1;
    params[1] = &arg2;
    params[2] = &arg3;
    
    fci.size           = sizeof(fci);
    fci.object_ptr     = object_pp ? *object_pp : NULL;
    fci.function_name  = &z_fname;
    fci.retval_ptr_ptr = retval_ptr_ptr ? retval_ptr_ptr : &retval;
    fci.param_count    = param_count;
    fci.params         = params;
    fci.no_separation  = 1;
    fci.symbol_table   = NULL;
    
    if (!fn_proxy && !obj_ce) {
        ZVAL_STRINGL(&z_fname, function_name, function_name_len, 0);
        fci.function_table = !object_pp ? EG(function_table) : NULL;
        result = zend_call_function(&fci, NULL TSRMLS_CC);
    } else {
        zend_fcall_info_cache fcic;
        fcic.initialized = 1;
        if (!obj_ce) {
            obj_ce = object_pp ? Z_OBJCE_PP(object_pp) : NULL;
        }
        if (obj_ce) {
            function_table = &obj_ce->function_table;
        } else {
            function_table = EG(function_table);
        }
        if (!fn_proxy || !*fn_proxy) {
            if (zend_hash_find(function_table, function_name, function_name_len+1, (void **) &fcic.function_handler) == FAILURE) {
                zend_error(E_CORE_ERROR, "Couldn't find implementation for method %s%s%s", obj_ce ? obj_ce->name : "", obj_ce ? "::" : "", function_name);
            }
            if (fn_proxy) {
                *fn_proxy = fcic.function_handler;
            }
        } else {
            fcic.function_handler = *fn_proxy;
        }
        fcic.calling_scope = obj_ce;
        if (object_pp) {
            fcic.called_scope = Z_OBJCE_PP(object_pp);
        } else if (obj_ce && 
                   !(EG(called_scope)) &&
                   instanceof_function(EG(called_scope), obj_ce TSRMLS_CC)) 
        {
            fcic.called_scope = obj_ce;
        } else {
            fcic.called_scope = EG(called_scope);
        }
        fcic.object_ptr = object_pp ? *object_pp : NULL;
        
        result = zend_call_function(&fci, &fcic TSRMLS_CC);
    }
    if (result == FAILURE) {
        if (!obj_ce) {
            obj_ce = object_pp ? Z_OBJCE_PP(object_pp) : NULL;
        }
        if (!EG(exception)) {
            zend_error(E_CORE_ERROR, "Couldn't execute method %s%s%s", obj_ce ? obj_ce->name : "", obj_ce ? "::" : "", function_name);
        }
    }
    if (!retval_ptr_ptr) {
        if (retval) {
            zval_ptr_dtor(&retval);
        }
        return NULL;
    }
    return *retval_ptr_ptr;
}
/* }}} */

/** {{{ proto public Yal\Acl\Acl::__construct(void)
 */
PHP_METHOD(yal_acl_acl, __construct) 
{
    zval *resources, *rules, *array_temp_1, *array_temp_2, *array_temp_3, *temp;
    MAKE_STD_ZVAL(resources);
    MAKE_STD_ZVAL(rules);
    MAKE_STD_ZVAL(array_temp_1);
    MAKE_STD_ZVAL(array_temp_2);
    MAKE_STD_ZVAL(array_temp_3);
    array_init(resources);
    array_init(rules);
    array_init(array_temp_1);
    array_init(array_temp_2);
    array_init(array_temp_3);
    
    add_assoc_zval(rules,          "byResourceId",  resources);
    add_assoc_string(array_temp_3, "type",          YAL_ACL_ACL_PROPERTY_NAME_TYPE_DENY, 1);
    add_assoc_null(array_temp_3,   "assert");
    add_assoc_zval(array_temp_2,   "allPrivileges", array_temp_3);
    add_assoc_zval(array_temp_2,   "byPrivilegeId", resources);
    add_assoc_zval(array_temp_1,   "allRoles",      array_temp_2);
    add_assoc_zval(array_temp_1,   "byRoleId",      resources);
    add_assoc_zval(rules,          "allResources",  array_temp_1);
    
    zend_update_property(yal_acl_acl_ce, getThis(), ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_RULES),     rules TSRMLS_CC);
    zend_update_property(yal_acl_acl_ce, getThis(), ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_RESOURCES), resources TSRMLS_CC);
    
    zval_ptr_dtor(&resources);
    zval_ptr_dtor(&rules);
    
    RETURN_TRUE;
}
/* }}} */

/** {{{ proto public Yal\Acl\Acl::addRole($role, $parents = null)
 */
PHP_METHOD(yal_acl_acl, addRole) 
{
    zval *role_interface, *parents, *role;
    zval *generic_role, *obj_registery;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &role_interface, &parents) == FAILURE) {
        RETURN_NULL();
    }
    
    if (IS_NULL == Z_TYPE_P(parents)) {
        MAKE_STD_ZVAL(parents);
        ZVAL_NULL(parents);
    }
    
    if (Z_TYPE_P(role_interface) == IS_STRING) {
        MAKE_STD_ZVAL(generic_role);
        object_init_ex(generic_role, yal_acl_role_generic_role_ce);
        zend_call_method_with_1_params(&generic_role, yal_acl_role_generic_role_ce, NULL, "__construct", &role, role_interface);
        zval_ptr_dtor(&generic_role);
    } else if (IS_OBJECT == Z_TYPE_P(role_interface) &&
        !instanceof_function(Z_OBJCE_P(role_interface), yal_acl_role_role_interface_ce TSRMLS_CC)) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "expects %s to be of type Yal\\Acl\\Role\\RoleInterface", Z_OBJVAL_P(role_interface));
        zval_ptr_dtor(&parents);
        zval_ptr_dtor(&role_interface);
        RETURN_FALSE;
    } else {
        MAKE_STD_ZVAL(role);
        *role = *role_interface;
        INIT_PZVAL(role);
        zval_copy_ctor(role);
    }
    zend_call_method_with_0_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "getroleregistry", &obj_registery);
    zend_call_method_with_2_params(&obj_registery, Z_OBJCE_P(obj_registery), NULL, "add", NULL, role, parents);
    
    zval_ptr_dtor(&role);
    zval_ptr_dtor(&obj_registery);
    RETURN_ZVAL(getThis(), 1, 0);
}
/* }}} */

/** {{{ proto public Yal\Acl\Acl::getRole(Role\RoleInterface|string $role)
 */
PHP_METHOD(yal_acl_acl, getRole) 
{
    zval *role, *registery_obj, *return_get_value;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &role) == FAILURE) {
        RETURN_NULL();
    }
    
    zend_call_method_with_0_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "getroleregistry", &registery_obj);
    zend_call_method_with_1_params(&registery_obj, Z_OBJCE_P(registery_obj), NULL, "get", &return_get_value, role);
    
    zval_ptr_dtor(&registery_obj);
    RETURN_ZVAL(return_get_value, 1, 0);
}
/* }}} */

/** {{{ proto public Yal\Acl\Acl::hasRole(Role\RoleInterface|string $role)
 */
PHP_METHOD(yal_acl_acl, hasRole) 
{
    zval *role, *registery_obj, *return_get_value;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &role) == FAILURE) {
        RETURN_NULL();
    }
    
    zend_call_method_with_0_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "getroleregistry", &registery_obj);
    zend_call_method_with_1_params(&registery_obj, Z_OBJCE_P(registery_obj), NULL, "has", &return_get_value, role);
    
    zval_ptr_dtor(&registery_obj);
    RETURN_ZVAL(return_get_value, 1, 0);
}
/* }}} */

/** {{{ proto public Yal\Acl\Acl::inheritsRole(Role\RoleInterface|string $role
 *                                             Role\RoleInterface|string $inherit
 *                                             bool $onlyParents)
 */
PHP_METHOD(yal_acl_acl, inheritsRole) 
{
    zval *role, *inherit, *registery_obj, *return_get_value, *only_parents;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz|z", &role, &inherit, &only_parents) == FAILURE) {
        RETURN_NULL();
    }
    
    zend_call_method_with_0_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "getroleregistry", &registery_obj);
    zend_call_method_with_3_params(&registery_obj, Z_OBJCE_P(registery_obj), NULL, "inherits", &return_get_value, role, inherit, only_parents);
    
    zval_ptr_dtor(&registery_obj);
    RETURN_ZVAL(return_get_value, 1, 0);
}
/* }}} */

/** {{{ proto public Yal\Acl\Acl::removeRole(Role\RoleInterface|string $role)
 */
PHP_METHOD(yal_acl_acl, removeRole) 
{
    zval *role, *rules, *registery_obj, *role_id;
    zval **rules_allresources, **rules_allresources_byroleid, **rules_byresourcedid;
    zval **visitor, **visitor_byroleid;
    HashPosition pointer, pointer_visitor;
    char *rules_allresources_byroleid_key, *resource_id_current, *role_id_current;
    uint rules_allresources_byroleid_key_len, resource_id_current_len, role_id_current_len;
    ulong rules_allresources_byroleid_num_key, resource_id_current_num_key, role_id_current_num_key;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &role) == FAILURE) {
        RETURN_NULL();
    }
    
    zend_call_method_with_0_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "getroleregistry", &registery_obj);
    zend_call_method_with_1_params(&registery_obj, Z_OBJCE_P(registery_obj), NULL, "remove", NULL, role);
    
    if (IS_OBJECT == Z_TYPE_P(role) &&
        instanceof_function(Z_OBJCE_P(role), yal_acl_role_role_interface_ce TSRMLS_CC)) {
        zend_call_method_with_0_params(&role, Z_OBJCE_P(role), NULL, "getroleid", &role_id);
    } else {
        MAKE_STD_ZVAL(role_id);
        *role_id = *role;
        INIT_PZVAL(role_id);
        zval_copy_ctor(role_id);
    }
    
    rules = zend_read_property(yal_acl_acl_ce, getThis(), ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_RULES), 1 TSRMLS_CC);
    
    if (zend_hash_find(Z_ARRVAL_P(rules), ZEND_STRS("allResources"), (void **)&rules_allresources) != SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Roles allResources not found");
        RETURN_FALSE;
    }
    if (zend_hash_find(Z_ARRVAL_PP(rules_allresources), ZEND_STRS("byRoleId"), (void **)&rules_allresources_byroleid) != SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Roles byRoleId not found");
        RETURN_FALSE;
    }
    
    if (zend_hash_num_elements(Z_ARRVAL_PP(rules_allresources_byroleid))) {
        zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(rules_allresources_byroleid), &pointer);
        while (zend_hash_get_current_key_ex(Z_ARRVAL_PP(rules_allresources_byroleid), &rules_allresources_byroleid_key, &rules_allresources_byroleid_key_len, &rules_allresources_byroleid_num_key, 0, &pointer)) {
            if (Z_TYPE_P(role_id) == IS_STRING && Z_STRVAL_P(role_id) == rules_allresources_byroleid_key) {
                zend_hash_del(Z_ARRVAL_PP(rules_allresources_byroleid), rules_allresources_byroleid_key, rules_allresources_byroleid_key_len);
            }
            zend_hash_move_forward_ex(Z_ARRVAL_PP(rules_allresources_byroleid), &pointer); 
        }
    }
    
    if (zend_hash_find(Z_ARRVAL_P(rules), ZEND_STRS("byResourceId"), (void **)&rules_byresourcedid) != SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Roles byResourceId not found");
        RETURN_FALSE;
    }
    
    if (zend_hash_num_elements(Z_ARRVAL_PP(rules_byresourcedid))) {
        zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(rules_byresourcedid), &pointer);
        while (zend_hash_get_current_data_ex(Z_ARRVAL_PP(rules_byresourcedid), (void**)&visitor, &pointer) == SUCCESS) {
            zend_hash_get_current_key_ex(Z_ARRVAL_PP(rules_byresourcedid), &resource_id_current, &resource_id_current_len, &resource_id_current_num_key, 0, &pointer);
            
            if (zend_hash_exists(Z_ARRVAL_PP(visitor), ZEND_STRS("byRoleId"))) {
                zend_hash_find(Z_ARRVAL_PP(visitor), ZEND_STRS("byRoleId"), (void **)&visitor_byroleid);
                zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(visitor_byroleid), &pointer_visitor);
                
                while (zend_hash_get_current_key_ex(Z_ARRVAL_PP(visitor_byroleid), &role_id_current, &role_id_current_len, &role_id_current_num_key, 0, &pointer_visitor)) {
                    if (Z_TYPE_P(role_id) == IS_STRING && Z_STRVAL_P(role_id) == role_id_current) {
                        
                        zval **rules_byresourcedid_resourceidcurrent, **rules_byresourcedid_resourceidcurrent_byroleid;
                        if (zend_hash_find(Z_ARRVAL_PP(rules_byresourcedid), resource_id_current, sizeof(resource_id_current)+1, (void **)&rules_byresourcedid_resourceidcurrent) != SUCCESS) {
                            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Roles '%s' not found", resource_id_current);
                            RETURN_FALSE;
                        }
                        if (zend_hash_find(Z_ARRVAL_PP(rules_byresourcedid_resourceidcurrent), ZEND_STRS("byRoleId"), (void **)&rules_byresourcedid_resourceidcurrent_byroleid) != SUCCESS) {
                            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Roles '%s' not found", resource_id_current);
                            RETURN_FALSE;
                        }

                        zend_hash_del(Z_ARRVAL_PP(rules_byresourcedid_resourceidcurrent_byroleid), role_id_current, role_id_current_len);
                    }
                    zend_hash_move_forward_ex(Z_ARRVAL_PP(visitor_byroleid), &pointer); 
                }
            }
            zend_hash_move_forward_ex(Z_ARRVAL_PP(rules_byresourcedid), &pointer); 
        }
    }
    zval_ptr_dtor(&role_id);
    RETURN_ZVAL(getThis(), 1, 0);
}
/* }}} */

/** {{{ proto public Yal\Acl\Acl::removeRoleAll(void)
 */
PHP_METHOD(yal_acl_acl, removeRoleAll) 
{
    zval *rules, *registery_obj;
    zval **rules_allresources, **rules_allresources_byroleid, **rules_byresourcedid;
    zval **visitor, **visitor_byroleid;
    HashPosition pointer, pointer_visitor;
    char *rules_allresources_byroleid_key, *resource_id_current, *role_id_current;
    uint rules_allresources_byroleid_key_len, resource_id_current_len, role_id_current_len;
    ulong rules_allresources_byroleid_num_key, resource_id_current_num_key, role_id_current_num_key;
    
    zend_call_method_with_0_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "getroleregistry", &registery_obj);
    zend_call_method_with_0_params(&registery_obj, Z_OBJCE_P(registery_obj), NULL, "removeall", NULL);
    
    rules = zend_read_property(yal_acl_acl_ce, getThis(), ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_RULES), 1 TSRMLS_CC);
    
    if (zend_hash_find(Z_ARRVAL_P(rules), ZEND_STRS("allResources"), (void **)&rules_allresources) != SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Roles allResources not found");
        RETURN_FALSE;
    }
    if (zend_hash_find(Z_ARRVAL_PP(rules_allresources), ZEND_STRS("byRoleId"), (void **)&rules_allresources_byroleid) != SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Roles byRoleId not found");
        RETURN_FALSE;
    }
    
    if (zend_hash_num_elements(Z_ARRVAL_PP(rules_allresources_byroleid))) {
        zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(rules_allresources_byroleid), &pointer);
        while (zend_hash_get_current_key_ex(Z_ARRVAL_PP(rules_allresources_byroleid), &rules_allresources_byroleid_key, &rules_allresources_byroleid_key_len, &rules_allresources_byroleid_num_key, 0, &pointer)) {
            zend_hash_del(Z_ARRVAL_PP(rules_allresources_byroleid), rules_allresources_byroleid_key, rules_allresources_byroleid_key_len);
            zend_hash_move_forward_ex(Z_ARRVAL_PP(rules_allresources_byroleid), &pointer); 
        }
    }
    
    if (zend_hash_find(Z_ARRVAL_P(rules), ZEND_STRS("byResourceId"), (void **)&rules_byresourcedid) != SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Roles byResourceId not found");
        RETURN_FALSE;
    }
    
    if (zend_hash_num_elements(Z_ARRVAL_PP(rules_byresourcedid))) {
        zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(rules_byresourcedid), &pointer);
        while (zend_hash_get_current_data_ex(Z_ARRVAL_PP(rules_byresourcedid), (void**)&visitor, &pointer) == SUCCESS) {
            zend_hash_get_current_key_ex(Z_ARRVAL_PP(rules_byresourcedid), &resource_id_current, &resource_id_current_len, &resource_id_current_num_key, 0, &pointer);

            zend_hash_find(Z_ARRVAL_PP(visitor), ZEND_STRS("byRoleId"), (void **)&visitor_byroleid);
            zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(visitor_byroleid), &pointer_visitor);
                
            while (zend_hash_get_current_key_ex(Z_ARRVAL_PP(visitor_byroleid), &role_id_current, &role_id_current_len, &role_id_current_num_key, 0, &pointer_visitor)) {
                zval **rules_byresourcedid_resourceidcurrent, **rules_byresourcedid_resourceidcurrent_byroleid;
                if (zend_hash_find(Z_ARRVAL_PP(rules_byresourcedid), resource_id_current, sizeof(resource_id_current)+1, (void **)&rules_byresourcedid_resourceidcurrent) != SUCCESS) {
                    php_error_docref(NULL TSRMLS_CC, E_WARNING, "Roles '%s' not found", resource_id_current);
                    RETURN_FALSE;
                }
                if (zend_hash_find(Z_ARRVAL_PP(rules_byresourcedid_resourceidcurrent), ZEND_STRS("byRoleId"), (void **)&rules_byresourcedid_resourceidcurrent_byroleid) != SUCCESS) {
                    php_error_docref(NULL TSRMLS_CC, E_WARNING, "Roles '%s' not found", resource_id_current);
                    RETURN_FALSE;
                }

                zend_hash_del(Z_ARRVAL_PP(rules_byresourcedid_resourceidcurrent_byroleid), role_id_current, role_id_current_len);
                zend_hash_move_forward_ex(Z_ARRVAL_PP(visitor_byroleid), &pointer); 
                }
            zend_hash_move_forward_ex(Z_ARRVAL_PP(rules_byresourcedid), &pointer); 
        }
    }
    
    RETURN_ZVAL(getThis(), 1, 0);
}
/* }}} */

/** {{{ proto public Yal\Acl\Acl::addResource(Resource\ResourceInterface|string $resource
 *                                            Resource\ResourceInterface|string $parent)
 */
PHP_METHOD(yal_acl_acl, addResource) 
{
    zval *resource, *parent = NULL, *generic_role, *resource_id, *hasresource_flag;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &resource, &parent) == FAILURE) {
        RETURN_FALSE;
    }
    
    if (IS_STRING == Z_TYPE_P(resource)) {
        MAKE_STD_ZVAL(generic_role);
        object_init_ex(generic_role, yal_acl_role_generic_role_ce);
        zend_call_method_with_1_params(&generic_role, yal_acl_role_generic_role_ce, NULL, "__construct", &resource, resource);
        zval_ptr_dtor(&generic_role);
    } else if (IS_OBJECT == Z_TYPE_P(resource) &&
        !instanceof_function(Z_OBJCE_P(resource), yal_acl_resource_resource_interface_ce TSRMLS_CC)) {
        
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "addResource() expects '%s' to be of type Ya\\Acl\\Resource\\ResourceInterface", Z_OBJCE_P(resource)->name);
        zval_ptr_dtor(&resource);
        zval_ptr_dtor(&generic_role);
        RETURN_FALSE;
    }
    
    zend_call_method_with_0_params(&resource, yal_acl_resource_generic_resource_ce, NULL, "getresourceid", &resource_id);
    zend_call_method_with_1_params(&getThis(), yal_acl_acl_ce, NULL, "hasresource", &hasresource_flag, resource_id);
    if (Z_BVAL_P(hasresource_flag)) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource id '%s' already exists in the ACL", Z_STRVAL_P(resource_id));
        zval_ptr_dtor(&resource);
        zval_ptr_dtor(&generic_role);
        zval_ptr_dtor(&resource_id);
    }
    
    zval *resource_parent;
    MAKE_STD_ZVAL(resource_parent);
    ZVAL_NULL(resource_parent);
    
    zval *resources;
    resources = zend_read_property(yal_acl_acl_ce, getThis(), ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_RESOURCES), 1 TSRMLS_CC);

    if (parent) {
        
        zval *resource_parent_id;
        
        if (IS_OBJECT == Z_TYPE_P(parent) &&
            instanceof_function(Z_OBJCE_P(parent), yal_acl_resource_resource_interface_ce TSRMLS_CC)) {
            zend_call_method_with_0_params(&parent, Z_OBJCE_P(parent), NULL, "getresourceid", &resource_parent_id);
        } else {
            MAKE_STD_ZVAL(resource_parent_id);
            *resource_parent_id = *parent;
            INIT_PZVAL(resource_parent_id);
            zval_copy_ctor(resource_parent_id);
        }
        
        zend_call_method_with_1_params(&getThis(), yal_acl_acl_ce, NULL, "getresource", &resource_parent, resource_parent_id);
        
        zval **resources_resourceparentid, **resources_resourceparentid_children;
        
        if (zend_hash_find(Z_ARRVAL_P(resources), Z_STRVAL_P(resource_parent_id), Z_STRLEN_P(resource_parent_id)+1, (void **)&resources_resourceparentid) != SUCCESS) {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource '%s' not found", Z_STRVAL_P(resource_parent_id));
            RETURN_FALSE;
        }
        if (zend_hash_find(Z_ARRVAL_PP(resources_resourceparentid), ZEND_STRS("children"), (void **)&resources_resourceparentid_children) != SUCCESS) {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource children not found");
            RETURN_FALSE;
        }
        zend_hash_update(Z_ARRVAL_PP(resources_resourceparentid_children), Z_STRVAL_P(resource_id), Z_STRLEN_P(resource_id)+1, &resource, sizeof(zval *), NULL);
    }
    
    zval *resources_resourceid, *array;
    MAKE_STD_ZVAL(resources_resourceid);
    MAKE_STD_ZVAL(array);
    array_init(resources_resourceid);
    array_init(array);
    add_assoc_zval(resources_resourceid, "instance", resource);
    add_assoc_zval(resources_resourceid, "parent",   resource_parent);
    add_assoc_zval(resources_resourceid, "children", array);
    
    zend_hash_update(Z_ARRVAL_P(resources), Z_STRVAL_P(resource_id), Z_STRLEN_P(resource_id)+1, &resources_resourceid, sizeof(zval *), NULL);
    
    RETURN_ZVAL(getThis(), 1, 0);
}
/* }}} */

/** {{{ proto public Yal\Acl\Acl::getResource(Resource\ResourceInterface|string $resource)
 */
PHP_METHOD(yal_acl_acl, getResource) 
{
    zval *resource, *resource_id, *hasresource_flag;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &resource) == FAILURE) {
        RETURN_FALSE;
    }
    
    if (IS_OBJECT == Z_TYPE_P(resource) &&
        instanceof_function(Z_OBJCE_P(resource), yal_acl_resource_resource_interface_ce TSRMLS_CC)) {
        zend_call_method_with_0_params(&resource, Z_OBJCE_P(resource), NULL, "getresourceid", &resource_id);
    } else {
        convert_to_string_ex(&resource);
        MAKE_STD_ZVAL(resource_id);
        *resource_id = *resource;
        INIT_PZVAL(resource_id);
        zval_copy_ctor(resource_id);
    }
    
    zend_call_method_with_1_params(&getThis(), yal_acl_acl_ce, NULL, "hasresource", &hasresource_flag, resource);
    if (!Z_BVAL_P(hasresource_flag)) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource '%s' not found", Z_STRVAL_P(resource_id));
        RETURN_FALSE;
    }
    
    zval *resources, **resources_resourceid, **resources_resourceid_instance;
    resources = zend_read_property(yal_acl_acl_ce, getThis(), ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_RESOURCES), 1 TSRMLS_CC);
    if (zend_hash_find(Z_ARRVAL_P(resources), Z_STRVAL_P(resource_id), Z_STRLEN_P(resource_id)+1, (void **)&resources_resourceid) != SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource '%s' not found", Z_STRVAL_P(resource_id));
        RETURN_FALSE;
    }
    if (zend_hash_find(Z_ARRVAL_PP(resources_resourceid), ZEND_STRS("instance"), (void **)&resources_resourceid_instance) != SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource instance not found");
        RETURN_FALSE;
    }
    RETURN_ZVAL(*resources_resourceid_instance, 1, 0);
}
/* }}} */

/** {{{ proto public Yal\Acl\Acl::hasResource(void)
 */
PHP_METHOD(yal_acl_acl, hasResource) 
{
    zval *resource, *resource_id, *resources;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &resource) == FAILURE) {
        RETURN_FALSE;
    }
    
    if (IS_OBJECT == Z_TYPE_P(resource) &&
        instanceof_function(Z_OBJCE_P(resource), yal_acl_resource_resource_interface_ce TSRMLS_CC)) {
        zend_call_method_with_0_params(&resource, Z_OBJCE_P(resource), NULL, "getresourceid", &resource_id);
    } else {
        convert_to_string_ex(&resource);
        MAKE_STD_ZVAL(resource_id);
        *resource_id = *resource;
        INIT_PZVAL(resource_id);
        zval_copy_ctor(resource_id);
    }
    resources = zend_read_property(yal_acl_acl_ce, getThis(), ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_RESOURCES), 1 TSRMLS_CC);
    
    RETURN_BOOL(zend_hash_exists(Z_ARRVAL_P(resources), Z_STRVAL_P(resource_id), Z_STRLEN_P(resource_id)+1));
}
/* }}} */

/** {{{ proto public Yal\Acl\Acl::inheritsResource(
 *                 Resource\ResourceInterface|string    $resource
 *                 Resource\ResourceInterface|string    inherit
 *                 bool                                 $onlyParent 
 *      )
 */
PHP_METHOD(yal_acl_acl, inheritsResource) 
{
    zval *resource, *inherit, *resource_id, *inherit_id;
    zend_bool only_parents;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz|b", &resource, &inherit, &only_parents) == FAILURE) {
        RETURN_NULL();
    }
    
    zval *resource_obj, *inherit_resource_obj;
    
    zend_call_method_with_1_params(&getThis(), yal_acl_acl_ce, NULL, "getresource", &resource_obj, resource);
    if (IS_OBJECT != Z_TYPE_P(resource_obj)) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource '%s' not found", Z_STRVAL_P(resource));
        RETURN_FALSE;
    }
    zend_call_method_with_0_params(&resource_obj, Z_OBJCE_P(resource_obj), NULL, "getresourceid", &resource_id);
    
    zend_call_method_with_1_params(&getThis(), yal_acl_acl_ce, NULL, "getresource", &inherit_resource_obj, inherit);
    if (IS_OBJECT != Z_TYPE_P(inherit)) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource '%s' not found", Z_STRVAL_P(inherit));
        RETURN_FALSE;
    }
    zend_call_method_with_0_params(&inherit_resource_obj, Z_OBJCE_P(inherit_resource_obj), NULL, "getresourceid", &inherit_id);
    
    zval_ptr_dtor(&resource_obj);
    zval_ptr_dtor(&inherit_resource_obj);
    
    zval *resources, *parent_id, **resources_resourceid, **resources_resourceid_parent;
    
    resources = zend_read_property(yal_acl_acl_ce, getThis(), ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_RESOURCES), 1 TSRMLS_CC);
    
    if (zend_hash_find(Z_ARRVAL_P(resources), Z_STRVAL_P(resource_id), Z_STRLEN_P(resource_id)+1, (void **)&resources_resourceid) != SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource '%s' not found", Z_STRVAL_P(resource_id));
        RETURN_FALSE;
    }
    
    if (zend_hash_find(Z_ARRVAL_PP(resources_resourceid), ZEND_STRS("parent"), (void **)&resources_resourceid_parent) != SUCCESS ||
                        IS_OBJECT != Z_TYPE_PP(resources_resourceid_parent)) {
        RETURN_FALSE;
    } else {
        zend_call_method_with_0_params(resources_resourceid_parent, Z_OBJCE_PP(resources_resourceid_parent), NULL, "getresourceid", &parent_id);
        zval result;
        is_identical_function(&result, inherit_id, parent_id TSRMLS_CC);
        if (Z_LVAL(result)) {
            RETURN_TRUE;
        } else if (only_parents) {
            RETURN_FALSE;
        }
        //zval_ptr_dtor(&result);
    }
    
    int flag = 1;
    while (flag) {
        zval **resources_parentid, **resources_parentid_parent;
        
        if (zend_hash_find(Z_ARRVAL_P(resources), Z_STRVAL_P(parent_id), Z_STRLEN_P(parent_id)+1, (void **)&resources_parentid) != SUCCESS) {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource '%s' not found", Z_STRVAL_P(parent_id));
            RETURN_FALSE;
        }
        
        if (zend_hash_find(Z_ARRVAL_PP(resources_parentid), ZEND_STRS("parent"), (void **)&resources_parentid_parent) == SUCCESS) {
            if (Z_TYPE_PP(resources_parentid_parent) == IS_OBJECT) {
                zend_call_method_with_0_params(resources_parentid_parent, Z_OBJCE_PP(resources_parentid_parent), NULL, "getresourceid", &parent_id);
                
                zval result;
                is_identical_function(&result, inherit_id, parent_id TSRMLS_CC);
                if (Z_LVAL(result)) {
                    RETURN_TRUE;
                }
            } else {
                flag = 0;
            }
        } else {
            flag = 0;
        }
    }
    RETURN_FALSE;
}
/* }}} */

/** {{{ proto public Yal\Acl\Acl::removeResource(Resource\ResourceInterface|string $resource)
 */
PHP_METHOD(yal_acl_acl, removeResource) 
{
    zval *resource, *rules, *resources, *resource_id;
    
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &resource) == FAILURE) {
        RETURN_NULL();
    }
    
    zval *resource_obj, *inherit_resource_obj;
    zend_call_method_with_1_params(&getThis(), yal_acl_acl_ce, NULL, "getresource", &resource_obj, resource);
    
    if (IS_OBJECT != Z_TYPE_P(resource_obj)) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource '%s' not found", Z_STRVAL_P(resource));
        RETURN_FALSE;
    }
    zend_call_method_with_0_params(&resource_obj, Z_OBJCE_P(resource_obj), NULL, "getresourceid", &resource_id);
    zval_add_ref(resource_id);
    
    zval *resources_removed;
    MAKE_STD_ZVAL(resources_removed);
    array_init(resources_removed);
    add_next_index_string(resources_removed, estrdup(resource_id), 0);
    
    resources = zend_read_property(yal_acl_acl_ce, getThis(), ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_RESOURCES), 1 TSRMLS_CC);
    
    zval **resources_resourceid, **resources_parentid_parent;
    if (zend_hash_find(Z_ARRVAL_P(resources), Z_STRVAL_P(resource_id), Z_STRLEN_P(resource_id)+1, (void **)&resources_resourceid) != SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource '%s' not found", Z_STRVAL_P(resource_id));
        RETURN_FALSE;
    }
    if (zend_hash_find(Z_ARRVAL_PP(resources_resourceid), ZEND_STRS("parent"), (void **)&resources_parentid_parent) != SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource '%s' not found", Z_STRVAL_P(resource_id));
        RETURN_FALSE;
    }
    
    
    if (Z_TYPE_PP(resources_parentid_parent) != IS_NULL) {
        zval *resource_parent_id;
        zend_call_method_with_0_params(resources_parentid_parent, Z_OBJCE_PP(resources_parentid_parent), NULL, "getresourceid", &resource_parent_id);
    
        zval **resources_resourceparentid, **resources_resourceparentid_parent;
        if (zend_hash_find(Z_ARRVAL_P(resources), Z_STRVAL_P(resource_parent_id), Z_STRLEN_P(resource_parent_id)+1, (void **)&resources_resourceparentid) != SUCCESS) {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource '%s' not found", Z_STRVAL_P(resource_parent_id));
            RETURN_FALSE;
        }
        if (zend_hash_find(Z_ARRVAL_PP(resources_resourceparentid), ZEND_STRS("parent"), (void **)&resources_resourceparentid_parent) != SUCCESS) {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource 'parent' not found");
            RETURN_FALSE;
        }
        
        zend_hash_del(Z_ARRVAL_PP(resources_resourceparentid_parent), Z_STRVAL_P(resource_id), Z_STRLEN_P(resource_id));
    }

    HashPosition pointer;
    zval **resources_parentid_children;
    char *resources_parentid_children_key;
    uint resources_parentid_children_key_len;
    ulong resources_parentid_children_num_key;
    
    if (zend_hash_find(Z_ARRVAL_PP(resources_resourceid), ZEND_STRS("children"), (void **)&resources_parentid_children) != SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource 'children' not found");
        RETURN_FALSE;
    }
    
    if (zend_hash_num_elements(Z_ARRVAL_PP(resources_parentid_children))) {
        zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(resources_parentid_children), &pointer);
        while (zend_hash_get_current_key_ex(Z_ARRVAL_PP(resources_parentid_children), &resources_parentid_children_key, &resources_parentid_children_key_len, &resources_parentid_children_num_key, 0, &pointer)) {
            
            zend_call_method_with_1_params(&getThis(), yal_acl_acl_ce, NULL, "removeresource", NULL, resources_parentid_children_key);
            add_next_index_string(resources_removed, estrdup(resources_parentid_children_key), 0);
            zend_hash_move_forward_ex(Z_ARRVAL_PP(resources_parentid_children), &pointer); 
        }
    }
    
    zval **rules_byresourceid;
    rules = zend_read_property(yal_acl_acl_ce, getThis(), ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_RULES), 1 TSRMLS_CC);
    if (zend_hash_find(Z_ARRVAL_P(rules), ZEND_STRS("byResourceId"), (void **)&rules_byresourceid) != SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Resource 'byResourceId' not found");
        RETURN_FALSE;
    }
    
    printf("%s\n", Z_ARRVAL_P(resources_removed));
    
    HashPointer poi;
    zval **resource_id_removed;
    if (zend_hash_num_elements(Z_ARRVAL_P(resources_removed))) {
        zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(resources_removed), &poi);
        while (zend_hash_get_current_data_ex(Z_ARRVAL_P(resources_removed), (void **)&resource_id_removed, &poi) == SUCCESS) {
            zval_add_ref(resource_id_removed);
            
            zval **non_value;
            HashPosition pos;
            char *rules_byresourceid_key;
            uint rules_byresourceid_key_len;
            ulong rules_byresourceid_num_key;
            
            if (zend_hash_num_elements(Z_ARRVAL_PP(rules_byresourceid))) {
                zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(rules_byresourceid), &pos);
                while (zend_hash_get_current_data_ex(Z_ARRVAL_PP(rules_byresourceid), (void **)&non_value, &pos) == SUCCESS) {
                    zend_hash_get_current_key_ex(Z_ARRVAL_PP(rules_byresourceid), &rules_byresourceid_key, &rules_byresourceid_key_len, &rules_byresourceid_num_key, 0, &pos);
                    
                    printf("%s\n", Z_STRVAL_PP(resource_id_removed));
                    printf("%s\n", rules_byresourceid_key);
                    
                    if (Z_STRVAL_PP(resource_id_removed) == rules_byresourceid_key) {
                        zend_hash_del(Z_ARRVAL_PP(rules_byresourceid), rules_byresourceid_key, rules_byresourceid_key_len);
                    }
                    
                    zend_hash_move_forward_ex(Z_ARRVAL_PP(rules_byresourceid), &pos); 
                }
            }
            zend_hash_move_forward_ex(Z_ARRVAL_P(resources_removed), &poi); 
        }
    }
    zend_hash_del(Z_ARRVAL_P(resources), Z_STRVAL_P(resource_id), Z_STRLEN_P(resource_id));
    RETURN_ZVAL(getThis(), 1, 0);
}
/* }}} */






/** {{{ proto public Yal\Acl\Acl::getRoleRegistry(void)
 */
PHP_METHOD(yal_acl_acl, getRoleRegistry) 
{
    zval *role_registry, *obj_registery;
    role_registry = zend_read_property(yal_acl_acl_ce, getThis(), ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_ROLE_REGISTER), 0 TSRMLS_CC);
    if (Z_TYPE_P(role_registry) == IS_NULL) {
        MAKE_STD_ZVAL(obj_registery);
        object_init_ex(obj_registery, yal_acl_role_registery_ce);
        *role_registry = *obj_registery;
        INIT_PZVAL(role_registry);
        zval_copy_ctor(role_registry);
        zval_ptr_dtor(&obj_registery);
    }
    RETURN_ZVAL(role_registry, 1, 0);
}
/* }}} */




/** {{{ proto public Yal\Acl\Acl::isAllowed(void)
 */
PHP_METHOD(yal_acl_acl, isAllowed) 
{
    RETURN_TRUE;
}
/* }}} */


/** {{{ yal_acl_acl_methods
 */
zend_function_entry yal_acl_acl_methods[] = {
    PHP_ME(yal_acl_acl, __construct,        NULL,                               ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
    PHP_ME(yal_acl_acl, addRole,            yal_acl_acl_add_role_arg,           ZEND_ACC_PUBLIC)
    PHP_ME(yal_acl_acl, getRole,            yal_acl_acl_get_role_arg,           ZEND_ACC_PUBLIC)
    PHP_ME(yal_acl_acl, hasRole,            yal_acl_acl_has_role_arg,           ZEND_ACC_PUBLIC)
    PHP_ME(yal_acl_acl, inheritsRole,       yal_acl_acl_inherits_role_arg,      ZEND_ACC_PUBLIC)
    PHP_ME(yal_acl_acl, removeRole,         yal_acl_acl_remove_role_arg,        ZEND_ACC_PUBLIC)
    PHP_ME(yal_acl_acl, removeRoleAll,      NULL,                               ZEND_ACC_PUBLIC)
    PHP_ME(yal_acl_acl, addResource,        yal_acl_acl_add_resource_arg,       ZEND_ACC_PUBLIC)
    PHP_ME(yal_acl_acl, getResource,        yal_acl_acl_get_resource_arg,       ZEND_ACC_PUBLIC)
    PHP_ME(yal_acl_acl, hasResource,        yal_acl_acl_has_resource_arg,       ZEND_ACC_PUBLIC)
    PHP_ME(yal_acl_acl, inheritsResource,   yal_acl_acl_inherits_resource_arg,  ZEND_ACC_PUBLIC)
    PHP_ME(yal_acl_acl, removeResource,     yal_acl_acl_remove_resource_arg,    ZEND_ACC_PUBLIC)
    
    PHP_ME(yal_acl_acl, getRoleRegistry,    NULL,                               ZEND_ACC_PROTECTED)
    
    PHP_ME(yal_acl_acl, isAllowed,          yal_acl_acl_is_allowed_arg,         ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};
/* }}} */

/** {{{ ZEND_MINIT_FUNCTION
 */
ZEND_MINIT_FUNCTION(yal_acl_acl)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Yal\\Acl\\Acl", yal_acl_acl_methods);
    yal_acl_acl_ce = zend_register_internal_class_ex(&ce, NULL, NULL TSRMLS_CC);
    //zend_class_implements(yal_acl_acl_ce TSRMLS_CC, 1, yal_acl_acl_interface_ce);
    yal_acl_acl_ce->ce_flags |= ZEND_ACC_FINAL_CLASS;
    
    zend_declare_property_null(yal_acl_acl_ce, ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_ROLE_REGISTER),        ZEND_ACC_PROTECTED TSRMLS_CC);
    zend_declare_property_null(yal_acl_acl_ce, ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_RESOURCES),            ZEND_ACC_PROTECTED TSRMLS_CC);
    zend_declare_property_null(yal_acl_acl_ce, ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_IS_ALLOWED_ROLE),      ZEND_ACC_PROTECTED TSRMLS_CC);
    zend_declare_property_null(yal_acl_acl_ce, ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_IS_ALLOWED_RESOURCE),  ZEND_ACC_PROTECTED TSRMLS_CC);
    zend_declare_property_null(yal_acl_acl_ce, ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_IS_ALLOWED_PRIVILEGE), ZEND_ACC_PROTECTED TSRMLS_CC);
    zend_declare_property_null(yal_acl_acl_ce, ZEND_STRL(YAL_ACL_ACL_PROPERTY_NAME_RULES),                ZEND_ACC_PROTECTED TSRMLS_CC);
    
    return SUCCESS;
}
/* }}} */

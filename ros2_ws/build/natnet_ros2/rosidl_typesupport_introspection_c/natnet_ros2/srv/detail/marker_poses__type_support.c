// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from natnet_ros2:srv/MarkerPoses.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "natnet_ros2/srv/detail/marker_poses__rosidl_typesupport_introspection_c.h"
#include "natnet_ros2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "natnet_ros2/srv/detail/marker_poses__functions.h"
#include "natnet_ros2/srv/detail/marker_poses__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void natnet_ros2__srv__MarkerPoses_Request__rosidl_typesupport_introspection_c__MarkerPoses_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  natnet_ros2__srv__MarkerPoses_Request__init(message_memory);
}

void natnet_ros2__srv__MarkerPoses_Request__rosidl_typesupport_introspection_c__MarkerPoses_Request_fini_function(void * message_memory)
{
  natnet_ros2__srv__MarkerPoses_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember natnet_ros2__srv__MarkerPoses_Request__rosidl_typesupport_introspection_c__MarkerPoses_Request_message_member_array[1] = {
  {
    "structure_needs_at_least_one_member",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(natnet_ros2__srv__MarkerPoses_Request, structure_needs_at_least_one_member),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers natnet_ros2__srv__MarkerPoses_Request__rosidl_typesupport_introspection_c__MarkerPoses_Request_message_members = {
  "natnet_ros2__srv",  // message namespace
  "MarkerPoses_Request",  // message name
  1,  // number of fields
  sizeof(natnet_ros2__srv__MarkerPoses_Request),
  false,  // has_any_key_member_
  natnet_ros2__srv__MarkerPoses_Request__rosidl_typesupport_introspection_c__MarkerPoses_Request_message_member_array,  // message members
  natnet_ros2__srv__MarkerPoses_Request__rosidl_typesupport_introspection_c__MarkerPoses_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  natnet_ros2__srv__MarkerPoses_Request__rosidl_typesupport_introspection_c__MarkerPoses_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t natnet_ros2__srv__MarkerPoses_Request__rosidl_typesupport_introspection_c__MarkerPoses_Request_message_type_support_handle = {
  0,
  &natnet_ros2__srv__MarkerPoses_Request__rosidl_typesupport_introspection_c__MarkerPoses_Request_message_members,
  get_message_typesupport_handle_function,
  &natnet_ros2__srv__MarkerPoses_Request__get_type_hash,
  &natnet_ros2__srv__MarkerPoses_Request__get_type_description,
  &natnet_ros2__srv__MarkerPoses_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_natnet_ros2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, natnet_ros2, srv, MarkerPoses_Request)() {
  if (!natnet_ros2__srv__MarkerPoses_Request__rosidl_typesupport_introspection_c__MarkerPoses_Request_message_type_support_handle.typesupport_identifier) {
    natnet_ros2__srv__MarkerPoses_Request__rosidl_typesupport_introspection_c__MarkerPoses_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &natnet_ros2__srv__MarkerPoses_Request__rosidl_typesupport_introspection_c__MarkerPoses_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "natnet_ros2/srv/detail/marker_poses__rosidl_typesupport_introspection_c.h"
// already included above
// #include "natnet_ros2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "natnet_ros2/srv/detail/marker_poses__functions.h"
// already included above
// #include "natnet_ros2/srv/detail/marker_poses__struct.h"


// Include directives for member types
// Member `x_position`
// Member `y_position`
// Member `z_position`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__MarkerPoses_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  natnet_ros2__srv__MarkerPoses_Response__init(message_memory);
}

void natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__MarkerPoses_Response_fini_function(void * message_memory)
{
  natnet_ros2__srv__MarkerPoses_Response__fini(message_memory);
}

size_t natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__size_function__MarkerPoses_Response__x_position(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Response__x_position(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Response__x_position(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__fetch_function__MarkerPoses_Response__x_position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Response__x_position(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__assign_function__MarkerPoses_Response__x_position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Response__x_position(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__resize_function__MarkerPoses_Response__x_position(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__size_function__MarkerPoses_Response__y_position(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Response__y_position(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Response__y_position(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__fetch_function__MarkerPoses_Response__y_position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Response__y_position(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__assign_function__MarkerPoses_Response__y_position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Response__y_position(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__resize_function__MarkerPoses_Response__y_position(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__size_function__MarkerPoses_Response__z_position(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Response__z_position(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Response__z_position(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__fetch_function__MarkerPoses_Response__z_position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Response__z_position(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__assign_function__MarkerPoses_Response__z_position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Response__z_position(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__resize_function__MarkerPoses_Response__z_position(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__MarkerPoses_Response_message_member_array[4] = {
  {
    "num_of_markers",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(natnet_ros2__srv__MarkerPoses_Response, num_of_markers),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(natnet_ros2__srv__MarkerPoses_Response, x_position),  // bytes offset in struct
    NULL,  // default value
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__size_function__MarkerPoses_Response__x_position,  // size() function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Response__x_position,  // get_const(index) function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Response__x_position,  // get(index) function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__fetch_function__MarkerPoses_Response__x_position,  // fetch(index, &value) function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__assign_function__MarkerPoses_Response__x_position,  // assign(index, value) function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__resize_function__MarkerPoses_Response__x_position  // resize(index) function pointer
  },
  {
    "y_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(natnet_ros2__srv__MarkerPoses_Response, y_position),  // bytes offset in struct
    NULL,  // default value
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__size_function__MarkerPoses_Response__y_position,  // size() function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Response__y_position,  // get_const(index) function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Response__y_position,  // get(index) function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__fetch_function__MarkerPoses_Response__y_position,  // fetch(index, &value) function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__assign_function__MarkerPoses_Response__y_position,  // assign(index, value) function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__resize_function__MarkerPoses_Response__y_position  // resize(index) function pointer
  },
  {
    "z_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(natnet_ros2__srv__MarkerPoses_Response, z_position),  // bytes offset in struct
    NULL,  // default value
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__size_function__MarkerPoses_Response__z_position,  // size() function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Response__z_position,  // get_const(index) function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Response__z_position,  // get(index) function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__fetch_function__MarkerPoses_Response__z_position,  // fetch(index, &value) function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__assign_function__MarkerPoses_Response__z_position,  // assign(index, value) function pointer
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__resize_function__MarkerPoses_Response__z_position  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__MarkerPoses_Response_message_members = {
  "natnet_ros2__srv",  // message namespace
  "MarkerPoses_Response",  // message name
  4,  // number of fields
  sizeof(natnet_ros2__srv__MarkerPoses_Response),
  false,  // has_any_key_member_
  natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__MarkerPoses_Response_message_member_array,  // message members
  natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__MarkerPoses_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__MarkerPoses_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__MarkerPoses_Response_message_type_support_handle = {
  0,
  &natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__MarkerPoses_Response_message_members,
  get_message_typesupport_handle_function,
  &natnet_ros2__srv__MarkerPoses_Response__get_type_hash,
  &natnet_ros2__srv__MarkerPoses_Response__get_type_description,
  &natnet_ros2__srv__MarkerPoses_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_natnet_ros2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, natnet_ros2, srv, MarkerPoses_Response)() {
  if (!natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__MarkerPoses_Response_message_type_support_handle.typesupport_identifier) {
    natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__MarkerPoses_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__MarkerPoses_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "natnet_ros2/srv/detail/marker_poses__rosidl_typesupport_introspection_c.h"
// already included above
// #include "natnet_ros2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "natnet_ros2/srv/detail/marker_poses__functions.h"
// already included above
// #include "natnet_ros2/srv/detail/marker_poses__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "natnet_ros2/srv/marker_poses.h"
// Member `request`
// Member `response`
// already included above
// #include "natnet_ros2/srv/detail/marker_poses__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  natnet_ros2__srv__MarkerPoses_Event__init(message_memory);
}

void natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_fini_function(void * message_memory)
{
  natnet_ros2__srv__MarkerPoses_Event__fini(message_memory);
}

size_t natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__size_function__MarkerPoses_Event__request(
  const void * untyped_member)
{
  const natnet_ros2__srv__MarkerPoses_Request__Sequence * member =
    (const natnet_ros2__srv__MarkerPoses_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Event__request(
  const void * untyped_member, size_t index)
{
  const natnet_ros2__srv__MarkerPoses_Request__Sequence * member =
    (const natnet_ros2__srv__MarkerPoses_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Event__request(
  void * untyped_member, size_t index)
{
  natnet_ros2__srv__MarkerPoses_Request__Sequence * member =
    (natnet_ros2__srv__MarkerPoses_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__fetch_function__MarkerPoses_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const natnet_ros2__srv__MarkerPoses_Request * item =
    ((const natnet_ros2__srv__MarkerPoses_Request *)
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Event__request(untyped_member, index));
  natnet_ros2__srv__MarkerPoses_Request * value =
    (natnet_ros2__srv__MarkerPoses_Request *)(untyped_value);
  *value = *item;
}

void natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__assign_function__MarkerPoses_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  natnet_ros2__srv__MarkerPoses_Request * item =
    ((natnet_ros2__srv__MarkerPoses_Request *)
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Event__request(untyped_member, index));
  const natnet_ros2__srv__MarkerPoses_Request * value =
    (const natnet_ros2__srv__MarkerPoses_Request *)(untyped_value);
  *item = *value;
}

bool natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__resize_function__MarkerPoses_Event__request(
  void * untyped_member, size_t size)
{
  natnet_ros2__srv__MarkerPoses_Request__Sequence * member =
    (natnet_ros2__srv__MarkerPoses_Request__Sequence *)(untyped_member);
  natnet_ros2__srv__MarkerPoses_Request__Sequence__fini(member);
  return natnet_ros2__srv__MarkerPoses_Request__Sequence__init(member, size);
}

size_t natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__size_function__MarkerPoses_Event__response(
  const void * untyped_member)
{
  const natnet_ros2__srv__MarkerPoses_Response__Sequence * member =
    (const natnet_ros2__srv__MarkerPoses_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Event__response(
  const void * untyped_member, size_t index)
{
  const natnet_ros2__srv__MarkerPoses_Response__Sequence * member =
    (const natnet_ros2__srv__MarkerPoses_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Event__response(
  void * untyped_member, size_t index)
{
  natnet_ros2__srv__MarkerPoses_Response__Sequence * member =
    (natnet_ros2__srv__MarkerPoses_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__fetch_function__MarkerPoses_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const natnet_ros2__srv__MarkerPoses_Response * item =
    ((const natnet_ros2__srv__MarkerPoses_Response *)
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Event__response(untyped_member, index));
  natnet_ros2__srv__MarkerPoses_Response * value =
    (natnet_ros2__srv__MarkerPoses_Response *)(untyped_value);
  *value = *item;
}

void natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__assign_function__MarkerPoses_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  natnet_ros2__srv__MarkerPoses_Response * item =
    ((natnet_ros2__srv__MarkerPoses_Response *)
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Event__response(untyped_member, index));
  const natnet_ros2__srv__MarkerPoses_Response * value =
    (const natnet_ros2__srv__MarkerPoses_Response *)(untyped_value);
  *item = *value;
}

bool natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__resize_function__MarkerPoses_Event__response(
  void * untyped_member, size_t size)
{
  natnet_ros2__srv__MarkerPoses_Response__Sequence * member =
    (natnet_ros2__srv__MarkerPoses_Response__Sequence *)(untyped_member);
  natnet_ros2__srv__MarkerPoses_Response__Sequence__fini(member);
  return natnet_ros2__srv__MarkerPoses_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(natnet_ros2__srv__MarkerPoses_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(natnet_ros2__srv__MarkerPoses_Event, request),  // bytes offset in struct
    NULL,  // default value
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__size_function__MarkerPoses_Event__request,  // size() function pointer
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Event__request,  // get_const(index) function pointer
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Event__request,  // get(index) function pointer
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__fetch_function__MarkerPoses_Event__request,  // fetch(index, &value) function pointer
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__assign_function__MarkerPoses_Event__request,  // assign(index, value) function pointer
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__resize_function__MarkerPoses_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(natnet_ros2__srv__MarkerPoses_Event, response),  // bytes offset in struct
    NULL,  // default value
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__size_function__MarkerPoses_Event__response,  // size() function pointer
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__get_const_function__MarkerPoses_Event__response,  // get_const(index) function pointer
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__get_function__MarkerPoses_Event__response,  // get(index) function pointer
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__fetch_function__MarkerPoses_Event__response,  // fetch(index, &value) function pointer
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__assign_function__MarkerPoses_Event__response,  // assign(index, value) function pointer
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__resize_function__MarkerPoses_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_message_members = {
  "natnet_ros2__srv",  // message namespace
  "MarkerPoses_Event",  // message name
  3,  // number of fields
  sizeof(natnet_ros2__srv__MarkerPoses_Event),
  false,  // has_any_key_member_
  natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_message_member_array,  // message members
  natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_message_type_support_handle = {
  0,
  &natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_message_members,
  get_message_typesupport_handle_function,
  &natnet_ros2__srv__MarkerPoses_Event__get_type_hash,
  &natnet_ros2__srv__MarkerPoses_Event__get_type_description,
  &natnet_ros2__srv__MarkerPoses_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_natnet_ros2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, natnet_ros2, srv, MarkerPoses_Event)() {
  natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, natnet_ros2, srv, MarkerPoses_Request)();
  natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, natnet_ros2, srv, MarkerPoses_Response)();
  if (!natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_message_type_support_handle.typesupport_identifier) {
    natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "natnet_ros2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "natnet_ros2/srv/detail/marker_poses__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers natnet_ros2__srv__detail__marker_poses__rosidl_typesupport_introspection_c__MarkerPoses_service_members = {
  "natnet_ros2__srv",  // service namespace
  "MarkerPoses",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // natnet_ros2__srv__detail__marker_poses__rosidl_typesupport_introspection_c__MarkerPoses_Request_message_type_support_handle,
  NULL,  // response message
  // natnet_ros2__srv__detail__marker_poses__rosidl_typesupport_introspection_c__MarkerPoses_Response_message_type_support_handle
  NULL  // event_message
  // natnet_ros2__srv__detail__marker_poses__rosidl_typesupport_introspection_c__MarkerPoses_Response_message_type_support_handle
};


static rosidl_service_type_support_t natnet_ros2__srv__detail__marker_poses__rosidl_typesupport_introspection_c__MarkerPoses_service_type_support_handle = {
  0,
  &natnet_ros2__srv__detail__marker_poses__rosidl_typesupport_introspection_c__MarkerPoses_service_members,
  get_service_typesupport_handle_function,
  &natnet_ros2__srv__MarkerPoses_Request__rosidl_typesupport_introspection_c__MarkerPoses_Request_message_type_support_handle,
  &natnet_ros2__srv__MarkerPoses_Response__rosidl_typesupport_introspection_c__MarkerPoses_Response_message_type_support_handle,
  &natnet_ros2__srv__MarkerPoses_Event__rosidl_typesupport_introspection_c__MarkerPoses_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    natnet_ros2,
    srv,
    MarkerPoses
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    natnet_ros2,
    srv,
    MarkerPoses
  ),
  &natnet_ros2__srv__MarkerPoses__get_type_hash,
  &natnet_ros2__srv__MarkerPoses__get_type_description,
  &natnet_ros2__srv__MarkerPoses__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, natnet_ros2, srv, MarkerPoses_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, natnet_ros2, srv, MarkerPoses_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, natnet_ros2, srv, MarkerPoses_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_natnet_ros2
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, natnet_ros2, srv, MarkerPoses)(void) {
  if (!natnet_ros2__srv__detail__marker_poses__rosidl_typesupport_introspection_c__MarkerPoses_service_type_support_handle.typesupport_identifier) {
    natnet_ros2__srv__detail__marker_poses__rosidl_typesupport_introspection_c__MarkerPoses_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)natnet_ros2__srv__detail__marker_poses__rosidl_typesupport_introspection_c__MarkerPoses_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, natnet_ros2, srv, MarkerPoses_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, natnet_ros2, srv, MarkerPoses_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, natnet_ros2, srv, MarkerPoses_Event)()->data;
  }

  return &natnet_ros2__srv__detail__marker_poses__rosidl_typesupport_introspection_c__MarkerPoses_service_type_support_handle;
}

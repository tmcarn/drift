// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from natnet_ros2:srv/MarkerPoses.idl
// generated code does not contain a copyright notice
#include "natnet_ros2/srv/detail/marker_poses__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
natnet_ros2__srv__MarkerPoses_Request__init(natnet_ros2__srv__MarkerPoses_Request * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
natnet_ros2__srv__MarkerPoses_Request__fini(natnet_ros2__srv__MarkerPoses_Request * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
natnet_ros2__srv__MarkerPoses_Request__are_equal(const natnet_ros2__srv__MarkerPoses_Request * lhs, const natnet_ros2__srv__MarkerPoses_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
natnet_ros2__srv__MarkerPoses_Request__copy(
  const natnet_ros2__srv__MarkerPoses_Request * input,
  natnet_ros2__srv__MarkerPoses_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

natnet_ros2__srv__MarkerPoses_Request *
natnet_ros2__srv__MarkerPoses_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  natnet_ros2__srv__MarkerPoses_Request * msg = (natnet_ros2__srv__MarkerPoses_Request *)allocator.allocate(sizeof(natnet_ros2__srv__MarkerPoses_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(natnet_ros2__srv__MarkerPoses_Request));
  bool success = natnet_ros2__srv__MarkerPoses_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
natnet_ros2__srv__MarkerPoses_Request__destroy(natnet_ros2__srv__MarkerPoses_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    natnet_ros2__srv__MarkerPoses_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
natnet_ros2__srv__MarkerPoses_Request__Sequence__init(natnet_ros2__srv__MarkerPoses_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  natnet_ros2__srv__MarkerPoses_Request * data = NULL;

  if (size) {
    data = (natnet_ros2__srv__MarkerPoses_Request *)allocator.zero_allocate(size, sizeof(natnet_ros2__srv__MarkerPoses_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = natnet_ros2__srv__MarkerPoses_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        natnet_ros2__srv__MarkerPoses_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
natnet_ros2__srv__MarkerPoses_Request__Sequence__fini(natnet_ros2__srv__MarkerPoses_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      natnet_ros2__srv__MarkerPoses_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

natnet_ros2__srv__MarkerPoses_Request__Sequence *
natnet_ros2__srv__MarkerPoses_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  natnet_ros2__srv__MarkerPoses_Request__Sequence * array = (natnet_ros2__srv__MarkerPoses_Request__Sequence *)allocator.allocate(sizeof(natnet_ros2__srv__MarkerPoses_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = natnet_ros2__srv__MarkerPoses_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
natnet_ros2__srv__MarkerPoses_Request__Sequence__destroy(natnet_ros2__srv__MarkerPoses_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    natnet_ros2__srv__MarkerPoses_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
natnet_ros2__srv__MarkerPoses_Request__Sequence__are_equal(const natnet_ros2__srv__MarkerPoses_Request__Sequence * lhs, const natnet_ros2__srv__MarkerPoses_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!natnet_ros2__srv__MarkerPoses_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
natnet_ros2__srv__MarkerPoses_Request__Sequence__copy(
  const natnet_ros2__srv__MarkerPoses_Request__Sequence * input,
  natnet_ros2__srv__MarkerPoses_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(natnet_ros2__srv__MarkerPoses_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    natnet_ros2__srv__MarkerPoses_Request * data =
      (natnet_ros2__srv__MarkerPoses_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!natnet_ros2__srv__MarkerPoses_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          natnet_ros2__srv__MarkerPoses_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!natnet_ros2__srv__MarkerPoses_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `x_position`
// Member `y_position`
// Member `z_position`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
natnet_ros2__srv__MarkerPoses_Response__init(natnet_ros2__srv__MarkerPoses_Response * msg)
{
  if (!msg) {
    return false;
  }
  // num_of_markers
  // x_position
  if (!rosidl_runtime_c__double__Sequence__init(&msg->x_position, 0)) {
    natnet_ros2__srv__MarkerPoses_Response__fini(msg);
    return false;
  }
  // y_position
  if (!rosidl_runtime_c__double__Sequence__init(&msg->y_position, 0)) {
    natnet_ros2__srv__MarkerPoses_Response__fini(msg);
    return false;
  }
  // z_position
  if (!rosidl_runtime_c__double__Sequence__init(&msg->z_position, 0)) {
    natnet_ros2__srv__MarkerPoses_Response__fini(msg);
    return false;
  }
  return true;
}

void
natnet_ros2__srv__MarkerPoses_Response__fini(natnet_ros2__srv__MarkerPoses_Response * msg)
{
  if (!msg) {
    return;
  }
  // num_of_markers
  // x_position
  rosidl_runtime_c__double__Sequence__fini(&msg->x_position);
  // y_position
  rosidl_runtime_c__double__Sequence__fini(&msg->y_position);
  // z_position
  rosidl_runtime_c__double__Sequence__fini(&msg->z_position);
}

bool
natnet_ros2__srv__MarkerPoses_Response__are_equal(const natnet_ros2__srv__MarkerPoses_Response * lhs, const natnet_ros2__srv__MarkerPoses_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // num_of_markers
  if (lhs->num_of_markers != rhs->num_of_markers) {
    return false;
  }
  // x_position
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->x_position), &(rhs->x_position)))
  {
    return false;
  }
  // y_position
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->y_position), &(rhs->y_position)))
  {
    return false;
  }
  // z_position
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->z_position), &(rhs->z_position)))
  {
    return false;
  }
  return true;
}

bool
natnet_ros2__srv__MarkerPoses_Response__copy(
  const natnet_ros2__srv__MarkerPoses_Response * input,
  natnet_ros2__srv__MarkerPoses_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // num_of_markers
  output->num_of_markers = input->num_of_markers;
  // x_position
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->x_position), &(output->x_position)))
  {
    return false;
  }
  // y_position
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->y_position), &(output->y_position)))
  {
    return false;
  }
  // z_position
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->z_position), &(output->z_position)))
  {
    return false;
  }
  return true;
}

natnet_ros2__srv__MarkerPoses_Response *
natnet_ros2__srv__MarkerPoses_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  natnet_ros2__srv__MarkerPoses_Response * msg = (natnet_ros2__srv__MarkerPoses_Response *)allocator.allocate(sizeof(natnet_ros2__srv__MarkerPoses_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(natnet_ros2__srv__MarkerPoses_Response));
  bool success = natnet_ros2__srv__MarkerPoses_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
natnet_ros2__srv__MarkerPoses_Response__destroy(natnet_ros2__srv__MarkerPoses_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    natnet_ros2__srv__MarkerPoses_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
natnet_ros2__srv__MarkerPoses_Response__Sequence__init(natnet_ros2__srv__MarkerPoses_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  natnet_ros2__srv__MarkerPoses_Response * data = NULL;

  if (size) {
    data = (natnet_ros2__srv__MarkerPoses_Response *)allocator.zero_allocate(size, sizeof(natnet_ros2__srv__MarkerPoses_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = natnet_ros2__srv__MarkerPoses_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        natnet_ros2__srv__MarkerPoses_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
natnet_ros2__srv__MarkerPoses_Response__Sequence__fini(natnet_ros2__srv__MarkerPoses_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      natnet_ros2__srv__MarkerPoses_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

natnet_ros2__srv__MarkerPoses_Response__Sequence *
natnet_ros2__srv__MarkerPoses_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  natnet_ros2__srv__MarkerPoses_Response__Sequence * array = (natnet_ros2__srv__MarkerPoses_Response__Sequence *)allocator.allocate(sizeof(natnet_ros2__srv__MarkerPoses_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = natnet_ros2__srv__MarkerPoses_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
natnet_ros2__srv__MarkerPoses_Response__Sequence__destroy(natnet_ros2__srv__MarkerPoses_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    natnet_ros2__srv__MarkerPoses_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
natnet_ros2__srv__MarkerPoses_Response__Sequence__are_equal(const natnet_ros2__srv__MarkerPoses_Response__Sequence * lhs, const natnet_ros2__srv__MarkerPoses_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!natnet_ros2__srv__MarkerPoses_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
natnet_ros2__srv__MarkerPoses_Response__Sequence__copy(
  const natnet_ros2__srv__MarkerPoses_Response__Sequence * input,
  natnet_ros2__srv__MarkerPoses_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(natnet_ros2__srv__MarkerPoses_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    natnet_ros2__srv__MarkerPoses_Response * data =
      (natnet_ros2__srv__MarkerPoses_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!natnet_ros2__srv__MarkerPoses_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          natnet_ros2__srv__MarkerPoses_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!natnet_ros2__srv__MarkerPoses_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "natnet_ros2/srv/detail/marker_poses__functions.h"

bool
natnet_ros2__srv__MarkerPoses_Event__init(natnet_ros2__srv__MarkerPoses_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    natnet_ros2__srv__MarkerPoses_Event__fini(msg);
    return false;
  }
  // request
  if (!natnet_ros2__srv__MarkerPoses_Request__Sequence__init(&msg->request, 0)) {
    natnet_ros2__srv__MarkerPoses_Event__fini(msg);
    return false;
  }
  // response
  if (!natnet_ros2__srv__MarkerPoses_Response__Sequence__init(&msg->response, 0)) {
    natnet_ros2__srv__MarkerPoses_Event__fini(msg);
    return false;
  }
  return true;
}

void
natnet_ros2__srv__MarkerPoses_Event__fini(natnet_ros2__srv__MarkerPoses_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  natnet_ros2__srv__MarkerPoses_Request__Sequence__fini(&msg->request);
  // response
  natnet_ros2__srv__MarkerPoses_Response__Sequence__fini(&msg->response);
}

bool
natnet_ros2__srv__MarkerPoses_Event__are_equal(const natnet_ros2__srv__MarkerPoses_Event * lhs, const natnet_ros2__srv__MarkerPoses_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!natnet_ros2__srv__MarkerPoses_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!natnet_ros2__srv__MarkerPoses_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
natnet_ros2__srv__MarkerPoses_Event__copy(
  const natnet_ros2__srv__MarkerPoses_Event * input,
  natnet_ros2__srv__MarkerPoses_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!natnet_ros2__srv__MarkerPoses_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!natnet_ros2__srv__MarkerPoses_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

natnet_ros2__srv__MarkerPoses_Event *
natnet_ros2__srv__MarkerPoses_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  natnet_ros2__srv__MarkerPoses_Event * msg = (natnet_ros2__srv__MarkerPoses_Event *)allocator.allocate(sizeof(natnet_ros2__srv__MarkerPoses_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(natnet_ros2__srv__MarkerPoses_Event));
  bool success = natnet_ros2__srv__MarkerPoses_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
natnet_ros2__srv__MarkerPoses_Event__destroy(natnet_ros2__srv__MarkerPoses_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    natnet_ros2__srv__MarkerPoses_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
natnet_ros2__srv__MarkerPoses_Event__Sequence__init(natnet_ros2__srv__MarkerPoses_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  natnet_ros2__srv__MarkerPoses_Event * data = NULL;

  if (size) {
    data = (natnet_ros2__srv__MarkerPoses_Event *)allocator.zero_allocate(size, sizeof(natnet_ros2__srv__MarkerPoses_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = natnet_ros2__srv__MarkerPoses_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        natnet_ros2__srv__MarkerPoses_Event__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
natnet_ros2__srv__MarkerPoses_Event__Sequence__fini(natnet_ros2__srv__MarkerPoses_Event__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      natnet_ros2__srv__MarkerPoses_Event__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

natnet_ros2__srv__MarkerPoses_Event__Sequence *
natnet_ros2__srv__MarkerPoses_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  natnet_ros2__srv__MarkerPoses_Event__Sequence * array = (natnet_ros2__srv__MarkerPoses_Event__Sequence *)allocator.allocate(sizeof(natnet_ros2__srv__MarkerPoses_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = natnet_ros2__srv__MarkerPoses_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
natnet_ros2__srv__MarkerPoses_Event__Sequence__destroy(natnet_ros2__srv__MarkerPoses_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    natnet_ros2__srv__MarkerPoses_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
natnet_ros2__srv__MarkerPoses_Event__Sequence__are_equal(const natnet_ros2__srv__MarkerPoses_Event__Sequence * lhs, const natnet_ros2__srv__MarkerPoses_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!natnet_ros2__srv__MarkerPoses_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
natnet_ros2__srv__MarkerPoses_Event__Sequence__copy(
  const natnet_ros2__srv__MarkerPoses_Event__Sequence * input,
  natnet_ros2__srv__MarkerPoses_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(natnet_ros2__srv__MarkerPoses_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    natnet_ros2__srv__MarkerPoses_Event * data =
      (natnet_ros2__srv__MarkerPoses_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!natnet_ros2__srv__MarkerPoses_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          natnet_ros2__srv__MarkerPoses_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!natnet_ros2__srv__MarkerPoses_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from natnet_ros2:srv/MarkerPoses.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "natnet_ros2/srv/marker_poses.hpp"


#ifndef NATNET_ROS2__SRV__DETAIL__MARKER_POSES__BUILDER_HPP_
#define NATNET_ROS2__SRV__DETAIL__MARKER_POSES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "natnet_ros2/srv/detail/marker_poses__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace natnet_ros2
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::natnet_ros2::srv::MarkerPoses_Request>()
{
  return ::natnet_ros2::srv::MarkerPoses_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace natnet_ros2


namespace natnet_ros2
{

namespace srv
{

namespace builder
{

class Init_MarkerPoses_Response_z_position
{
public:
  explicit Init_MarkerPoses_Response_z_position(::natnet_ros2::srv::MarkerPoses_Response & msg)
  : msg_(msg)
  {}
  ::natnet_ros2::srv::MarkerPoses_Response z_position(::natnet_ros2::srv::MarkerPoses_Response::_z_position_type arg)
  {
    msg_.z_position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::natnet_ros2::srv::MarkerPoses_Response msg_;
};

class Init_MarkerPoses_Response_y_position
{
public:
  explicit Init_MarkerPoses_Response_y_position(::natnet_ros2::srv::MarkerPoses_Response & msg)
  : msg_(msg)
  {}
  Init_MarkerPoses_Response_z_position y_position(::natnet_ros2::srv::MarkerPoses_Response::_y_position_type arg)
  {
    msg_.y_position = std::move(arg);
    return Init_MarkerPoses_Response_z_position(msg_);
  }

private:
  ::natnet_ros2::srv::MarkerPoses_Response msg_;
};

class Init_MarkerPoses_Response_x_position
{
public:
  explicit Init_MarkerPoses_Response_x_position(::natnet_ros2::srv::MarkerPoses_Response & msg)
  : msg_(msg)
  {}
  Init_MarkerPoses_Response_y_position x_position(::natnet_ros2::srv::MarkerPoses_Response::_x_position_type arg)
  {
    msg_.x_position = std::move(arg);
    return Init_MarkerPoses_Response_y_position(msg_);
  }

private:
  ::natnet_ros2::srv::MarkerPoses_Response msg_;
};

class Init_MarkerPoses_Response_num_of_markers
{
public:
  Init_MarkerPoses_Response_num_of_markers()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MarkerPoses_Response_x_position num_of_markers(::natnet_ros2::srv::MarkerPoses_Response::_num_of_markers_type arg)
  {
    msg_.num_of_markers = std::move(arg);
    return Init_MarkerPoses_Response_x_position(msg_);
  }

private:
  ::natnet_ros2::srv::MarkerPoses_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::natnet_ros2::srv::MarkerPoses_Response>()
{
  return natnet_ros2::srv::builder::Init_MarkerPoses_Response_num_of_markers();
}

}  // namespace natnet_ros2


namespace natnet_ros2
{

namespace srv
{

namespace builder
{

class Init_MarkerPoses_Event_response
{
public:
  explicit Init_MarkerPoses_Event_response(::natnet_ros2::srv::MarkerPoses_Event & msg)
  : msg_(msg)
  {}
  ::natnet_ros2::srv::MarkerPoses_Event response(::natnet_ros2::srv::MarkerPoses_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::natnet_ros2::srv::MarkerPoses_Event msg_;
};

class Init_MarkerPoses_Event_request
{
public:
  explicit Init_MarkerPoses_Event_request(::natnet_ros2::srv::MarkerPoses_Event & msg)
  : msg_(msg)
  {}
  Init_MarkerPoses_Event_response request(::natnet_ros2::srv::MarkerPoses_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_MarkerPoses_Event_response(msg_);
  }

private:
  ::natnet_ros2::srv::MarkerPoses_Event msg_;
};

class Init_MarkerPoses_Event_info
{
public:
  Init_MarkerPoses_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MarkerPoses_Event_request info(::natnet_ros2::srv::MarkerPoses_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_MarkerPoses_Event_request(msg_);
  }

private:
  ::natnet_ros2::srv::MarkerPoses_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::natnet_ros2::srv::MarkerPoses_Event>()
{
  return natnet_ros2::srv::builder::Init_MarkerPoses_Event_info();
}

}  // namespace natnet_ros2

#endif  // NATNET_ROS2__SRV__DETAIL__MARKER_POSES__BUILDER_HPP_

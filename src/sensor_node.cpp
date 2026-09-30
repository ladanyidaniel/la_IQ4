#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/relative_humidity.hpp"
#include "sensor_msgs/msg/temperature.hpp"

class SensorNode : public rclcpp::Node
{
public:
  SensorNode() : Node("sensor_node")
  {
    temp_pub_ = create_publisher<sensor_msgs::msg::Temperature>(
      "temperature", 10);

    humidity_pub_ = create_publisher<sensor_msgs::msg::RelativeHumidity>(
      "humidity", 10);

    publish_data();
  }

private:
  void publish_data()
  {
    double temperature = 15 + rand() % 26;
    double humidity = 25 + rand() % 56;

    sensor_msgs::msg::Temperature temp_msg;
    temp_msg.temperature = temperature;
    temp_pub_->publish(temp_msg);

    sensor_msgs::msg::RelativeHumidity humidity_msg;
    humidity_msg.relative_humidity = humidity / 100.0;
    humidity_pub_->publish(humidity_msg);

    RCLCPP_INFO(
      get_logger(),
      "Temperature: %.0f C, humidity: %.0f %%",
      temperature,
      humidity);
  }

  rclcpp::Publisher<sensor_msgs::msg::Temperature>::SharedPtr temp_pub_;
  rclcpp::Publisher<sensor_msgs::msg::RelativeHumidity>::SharedPtr humidity_pub_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SensorNode>());
  rclcpp::shutdown();
  return 0;
}
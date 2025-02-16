import launch
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription([
        launch_ros.actions.Node(
            package='thermal_camera',
            executable='thermal_camera_node',
            name='thermal_camera_node',
            output='screen',
            parameters=[]
        )
    ])

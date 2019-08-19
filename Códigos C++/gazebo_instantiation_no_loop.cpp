/*
Sergio Gonzalez Muriel
Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
Code for instantiating a simulation in gazebo
*/

#include <bits/stdc++.h> 
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

#define MAX_X 2
#define MIN_X 2
#define MAX_Y 0.0
#define MIN_Y 0.0
// Number of box.urdf to use (box_1 z-size=0.1, box_2 z-size=0.2...)
#define MIN_BOX 3
#define MAX_BOX 5

using namespace std;

int main(int argc, char const *argv[])
{
    int status;
    // Open an empty world in gazebo
    status = system("xterm -hold -e \"roslaunch gazebo_ros empty_world.launch paused:=true\" &");
    if (status == 0){
        sleep(6);
        int x = MIN_X + ((double)rand()/double(RAND_MAX))* (MAX_X-MIN_X);
        int y = MIN_Y + ((double)rand()/double(RAND_MAX))* (MAX_Y-MIN_Y);
        int box = MIN_BOX + ((double)rand()/double(RAND_MAX))* (MAX_BOX-MIN_BOX);
        float z = 0.05*(float)box;
        stringstream xterm_box; stringstream xterm_object; 
        xterm_box << "xterm +hold -e \"rosrun gazebo_ros spawn_model -file box_" << box << ".urdf -urdf -x " << x
                << " -z " << z << " -y " << y << " -model box\" &";
        xterm_object << "xterm +hold -e \"rosrun gazebo_ros spawn_model -file cylinder.urdf -urdf -x " 
                    << (x - 0.45) << " -z " << (z*2+0.05) << " -y " << y << " -model red_object\" &";
        string str(xterm_box.str());
        const char* xterm_box_str = str.c_str();
        system(xterm_box_str);
        sleep(3);
        str = xterm_object.str();
        const char* xterm_object_str = str.c_str();
        system(xterm_object_str);
        sleep(3);
        stringstream xterm_wall;
        xterm_wall << "xterm +hold -e \"rosrun gazebo_ros spawn_model -file wall.urdf -urdf -x " 
                    << (x - 0.5) << " -y " << (y+3) << " -model wall\" &";
        str = xterm_wall.str();
        const char* xterm_wall_str = str.c_str(); 
        system(xterm_wall_str);
        sleep(3);
        stringstream xterm_wall1;
        xterm_wall1 << "xterm +hold -e \"rosrun gazebo_ros spawn_model -file wall.urdf -urdf -x " 
                    << (x - 0.5) << " -y " << (y-3) << " -model wall1\" &";
        str = xterm_wall1.str();
        xterm_wall_str = str.c_str(); 
        system(xterm_wall_str);
        sleep(3);
        stringstream xterm_wall2;
        xterm_wall2 << "xterm +hold -e \"rosrun gazebo_ros spawn_model -file wall2.urdf -urdf -x " 
                    << (- 0.5) << " -y " << y << " -model wall2\" &";
        str = xterm_wall2.str();
        xterm_wall_str = str.c_str(); 
        system(xterm_wall_str);
        sleep(3);
        stringstream xterm_wall3;
        xterm_wall3 << "xterm +hold -e \"rosrun gazebo_ros spawn_model -file wall2.urdf -urdf -x " 
                    << (x/2- 0.5) << " -y " << y+5.55 << " -Y " << M_PI/2 << " -model wall3\" &";
        str = xterm_wall3.str();
        xterm_wall_str = str.c_str(); 
        system(xterm_wall_str);
        sleep(3);
        stringstream xterm_wall4;
        xterm_wall4 << "xterm +hold -e \"rosrun gazebo_ros spawn_model -file wall2.urdf -urdf -x " 
                    << (x/2- 0.5) << " -y " << y-5.55 << " -Y " << M_PI/2 << " -model wall4\" &";
        str = xterm_wall4.str();
        xterm_wall_str = str.c_str(); 
        system(xterm_wall_str);
        sleep(3);

        // Instantiate a turtlebot in that empty world
        system("xterm -hold -e \"roslaunch crumb_gazebo test.launch\" &");
        sleep(10);
        // Unpause simulation
        system("rosservice call /gazebo/unpause_physics");   
    }else{
        system("killall -9 xterm gzserver");
    }
    return 0;
}

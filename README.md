# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## What is PID ? 

PID is one of traditional theory to control using proportional, integral and derivatives parameters, this methodology is used to adjust eg. temparature for the electric devices to give stable condition for the indoor temparature automatically. PID controller exploits the present, past and future information of prediction error to controll the feedback of the system. PID is easily developed and embedded in the system circuit to implement the algorythm. 

__PID stands for__;
* __Proportional__ - The controller is proportionaly responeded to the current error.
* __Integral__ - It counters continuous error, such as steering bias, by accumulating it over time.
* __Derivatives__ - It tries to predict and counter future error based on its current rate of change, therefore it will dampen the response of the proportional controller

As PID continously calculates error, which is the difference between the measured system output and the desired optimal output, PID of the steering controls difference between the target trajectory and car’s center, and PID of throttle controls difference between the target desired speed and the car's actual speed. 


[//]: # (Image References)

[onlykp01]:./data/only_kp_0.11.png "kp parameter"
[onlykp03]:./data/only_kp_0.3.png "kp parameter"
[kp02kd25]:./data/kp0.11_kd2.png "kp parameter"
[kp02kd25ki]:./data/kp0.11_kd2_ki0.0001.png "kp parameter"
[throttle]:./data/throttle.png "kp parameter"
[mov]:./mov/kp0.11_kd0.2.mov "mov" 


#### Controls P parameter (based on manual tuning)

By changing the fixed value __kp__, we see how the steering value is changed and how car roll out the drivable track surface after several time steps. 
The below graph shows the steering error when setting __kp=0.11__. The waves gradually divesed to the maximul value of the steering, then finally car roll out the road cources and stack in the field. Car start to wave the body beyond arounds step 1200. 
![alt text][onlykp01]
In the contrast, below graph shows the steering value error when setting __kp=0.3__. As we can see the line chart, car starts to flip the steering right and left beyond step 600 which is faster than previous example, and then the car run out the track road around step 700. 
![alt text][onlykp03]

Though __kp=0.11__ could be best value to control the steering error, only single fixed parameter P and kp cannot lap a car around the track road. We need another approach to avoid such overshooting which results to produce oscillating car.    
Next we try to solve with PD controller.

#### Controls P&D parameter 
Assuming fixe value __kp=0.11__ would be candidate parameter to control P parameters, we will search __kd__ value manually to set the best value for the car driving on the course.
After a number of try and error adjustments for kd value, I figured out __kd=2__ took best combination to have smooth driving a car on the track. The graph shows stable and smooth tracking error, which results to simulating lap the car around the ground track without any accidental happening.  

![alt text][kp02kd25] 

#### Add Integral of Error (controlling PID)
As Thrun explained in the video, normal steering model leads to a trajectory a far way from the final goal.
To do setting the long term bias close to the true goal, 
we need to make approach accumulattion steering bias as the time goes. It is sum of all cross tracking error.
First of all, we set a tiny numerical figure (eg. 0,0001) for __ki__ fixed parameter, and then try to run the simulation.
Following graph indicates __kp=0.11__, __kd=0.2__ and __ki=0.0001__ fixed paramters settings which leads the simulation car
lap the track circuit without troubles.

![alt text][kp02kd25ki] 


#### Controll throttle.
As I did same approach to adjust kp kd and ki fixed paramters for the steering value, 
I also have setup throttle PID controller as follows; Graph indicates how the trottle changes the car speed of the simulator.  
At first glance, car needs maximum throttle to accelerate the car upto the max speed, then keep slight adjustments according to the speed cte (= speed - max_speed).
![alt text][throttle] 

Here's a [link to my video result (controll steering and throttle with PID.)](./mov/steer_throttle.mp4)

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).


README.md
Team Number: 46
Member Names: Joseph Langevin (lang1107), Janani Kannan (kanna128), Gabe Molitor (molit104), Lorenzo Vega (vega0041)


-What is the project about (overview of the whole project, not just the hw4)?
The goal of this project is to create an environment for testing the functionality of a battery powered drone delivery system in a simulated environment. We wanted to extend the drone delivery system we made in class to be more realistic in its implementation by making the drones battery powered, and then collecting data from the simulation in the form of .csv files. By collecting data from the simulation and comparing results while changing the number of drones and battery charging stations, we can develop an optimal strategy for implementing drone infrastructure on the U of M Twin Cities campus.


-How to run the simulation:
First, type "make -j" in the top level folder
Then, run the command "./build/bin/transit_service <PORT> apps/transit_service/web/" where PORT is the port number to specify

-What does the simulation do specifically?
The simulation lets us schedule trips from one destination to another within the bounds of UMN Twin Cities campus. There are two main components that the user interacts with: a scheduler window that lets you specify a robot’s pick up and drop off destination and what path-finding algorithm to use to accomplish it, and a simulation window that lets you observe the drone as it completes the scheduled trip. Before each trip, the drone checks to see if there is enough charge left in its battery to reach the pick up location, take the robot to the dropoff location, and make it to a charging station afterwards without running out of battery. Once you chart a trip in the scheduler, you can then observe the drone in the simulation as it completes the route, or stops at a charging station to charge up before embarking on the trip.

-New Feature (Singleton)
Our first feature is data collection via the Singleton Design pattern. It repeatedly collects data information regarding the Drones in our simulation system. This data includes total distance traveled, total decrease in fuel, number of trips, and number of stops at recharge stations. This is significantly interesting as our data offers insights into the performance of the various Routing Algorithms. From our CSV one is able to determine the distance a strategy travels, along with total fuel consumption of a drone using this particular strategy. It adds to existing work as we had to implement the Singleton design pattern as a class and had to include various update functions to accurately capture the data. We implemented this with Singleton as it provides a single reference only into a class; this is beneficial since all of the data about the drone can be accessed through this one class. Our new feature will automatically collect data throughout the simulation. To get this data to be outputted, click the Print CSV button. Within the current directory (top folder), this data will be represented in a CSV file called DataLog.csv.

-New Feature (Battery):
Our second feature that we implemented to our simulation was a battery system, including individual batteries that power drones and deplete over time, as well as charging stations for the drones to recharge their batteries with. We decided to use the decorator design pattern because it is an efficient way to add new functionality to a pre-existing object without changing any base implementation, thus keeping the program open to extension. 

Our new decorator overrides the original drone logic for moving between trips. We created an abstract DroneDecorator which contains a Drone. DroneDecorator inherits from Drone, and automatically calls the corresponding methods on this drone. BatteryDecorator inherits from this template, and overwrites the relevant methods (in this case Update()). BatteryDecorator keeps track of the charge in a float, decrementing it as the drone moves. Its Update() method reroutes the drone to a charger if the battery falls below 20%. Along with this, we added a charger factory, which creates charger entities placed around the map according to the json file.

Originally, our idea was to first check to see if there’s sufficient energy left in the battery to complete a trip without running out of energy during the journey before embarking.  Our plan was to create a dummy Drone object in a NeedsCharge() method that runs through the drone’s path, then moves to a charger. The method would return whether the dummy drone ran out of battery on the flight. However, there were a number of serious problems we ran into. Our simDrone would affect the real Drone’s path variables, which caused the actual drone’s pathfinding to break. The simDrone would also change the availability status of our Battery’s Drone. When trying to solve these issues through adding operator overloads to all relevant classes, the simulation would segfault upon simDrone’s deletion. We believe this was because one or more of Drone’s member variables weren’t being assigned or copied properly in our constructors. When another method tried to use or change these variables, the program crashed. The Drone object ended up being a poor fit for what we needed, breaking the simulation if information irrelevant to our needs wasn’t properly initialized. If we were to implement the battery logic again, we’d probably create a new kind of object specialized in checking a path, rather than trying to reuse the Drone class.

Ultimately, we chose to have the Drone automatically charge when its battery falls under 20%. This method has the added bonus of allowing the drone to charge between trips, rather than having to check as a trip is scheduled. With the added battery function, the simulation ends up being more realistic and data collection offers more insight by accounting for downtime needed for refueling in the  drones’ routes. This feature is not interactable, with DroneFactory now creating Drones within a battery wrapper by default.

-Link to Docker Submission:

-Link to Youtube video:

-Sprint retrospective:
Using sprints during our development process helped us approach the requirements of the assignment from a much more solid foundation than if we had simply chosen to work on it individually. By breaking up the project into smaller goals, and planning a sprint to maintain and manage those goals, we were able to define a much clearer plan for each of the tasks we completed. This project had both the largest scope and the least clearly defined set of instructions of any assignment we worked on this semester. By using the sprint structure, we were able to stay on track as we discovered new information and requirements, which helped us successfully adapt and implement all the different features needed for our extension much faster than if we hadn’t communicated during the process.

-UML Diagram: https://drive.google.com/file/d/1J6idi2MIRxngOQjeNfK5N2W2ohXCk8_a/view?usp=sharing



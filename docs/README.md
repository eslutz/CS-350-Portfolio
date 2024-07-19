# CS-350-Portfolio

Portfolio containing the projects from CS-350 Emerging Systems Architecture &amp; Technology.

## Projects

### Project 1

- [Guidelines & Requirements](Project%201%20-%20guidelines%20and%20rubric.pdf)
- [Report](./Project%201%20-%20report.pdf)
- Task Scheduler
![Project 1 task scheduler diagram](./Project%201%20-%20task%20scheduler.png)
- Demo Video
![Project 1 demo video](./Project%201%20-%20demo%20video.mov)

### Milestone 3

- [Guidelines & Requirements](./Milestone%203%20-%20guidelines%20and%20rubric.pdf)
- [Report](./Milestone%203%20-%20guidelines%20and%20rubric.pdf)
- State Diagram
![Milestone 3 state diagram](./Milestone%203%20-%20state%20diagram.png)
- Demo Video
![Milestone 3 demo video](./Milestone%203%20-%20demo%20video.mov)

### Milestone 2

- [Guidelines & Requirements](./Milestone%202%20-%20guidelines%20and%20rubric.pdf)
- [Report](./Milestone%202%20-%20guidelines%20and%20rubric.pdf)
- State Diagram
![Milestone 2 state diagram](./Milestone%202%20-%20state%20diagram.png)
- Demo Video
![Milestone 2 demo video](./Milestone%202%20-%20demo%20video.mov)

### Milestone 1

- [Guidelines & Requirements](./Milestone%201%20-%20guidelines%20and%20rubric.pdf)
- [Report](./Milestone%201%20-%20guidelines%20and%20rubric.pdf)
- Demo Video
![Milestone 1 demo video](./Milestone%201%20-%20demo%20video.mov)

## Course Reflection

### Summarize the project and what problem it was solving

The two projects I felt I did the best on were the final project creating the thermostat prototype and the Morse code project for milestone three.

The thermostat project involved creating a task scheduler that would use the temperature sensor to check the ambient temperature and compare that against a set point to determine if the heating system, represented by an LED, should be turned on or off.  Additionally, the two buttons on the device could be used to adjust the temperature set point up or down.  The task scheduler would check if a button had been pressed every 200ms, check the ambient temperature ever 500ms, and determine if heat was needed and turn on or off the LED accordingly every second.  At that time, it would also report the current status of the device via UART.  The message contained the room temperature, set-point temperature, heating state (on or off), and the current runtime in seconds.

The Morse code project displayed two messages in Morse code.  The two messages, 'SOS' and 'OK', were displayed one at a time on a continuous loop.  You would switch between messages by pressing one of the buttons.  This was accomplished using two LEDs and a state machine to determine is an LED should be on or off.  Turning the red LED on for 500ms represented a dot and turning on the green LED for 1500ms represented a dash.  There was a 1500ms pause with both LEDs off between each character of the message and another 3500ms pause between each word.  If the button was pressed to switch messages while a message was being displayed, the current message would finish displaying and before the new message would start.

### What did you do particularly well?

I feel I did particularly well at breaking each project up into smaller parts.  This allowed me to complete a small section at a time, without feeling overwhelmed.  I also feel that I did a good job of planning out the flow of the program before I started coding.  This allowed me to write the code in a logical order and made it easier to debug when I ran into issues.

### Where could you improve?

While I did a decent job of thinking out how the program would work and the flow of it, and then transferring that into code, I had trouble creating the state diagram documentation.  I had a difficult time translating what I was thinking and writing in code into a state diagram that made sense.  I think this is something that I could improve on with more practice.

### What tools and/or resources are you adding to your support network?

During the course of these projects, I learned a lot about embedded systems and how to program them.  This is not something that I had any experience with prior to this class.  It was a great learning experience covering topics, tools, and languages that I had not used before.  Since there was so much new material for me to learn, I found myself using a lot of different resources to help me understand the material.  The documentation available for the TI microcontroller proved to be a valuable resource.

### What skills from this project will be particularly transferable to other projects and/or course work?

The skills I gained from these projects is a stronger ability to think about and plan the flow of a program and how to break it up into smaller chunks.  This is a very useful skill that I will be able to use in future projects.

### How did you make this project maintainable, readable, and adaptable?

I made this project maintainable, readable, and adaptable by using good coding practices.  I used descriptive variable names, commented my code, and used functions to break up the code into smaller chunks.  I also used a state machine to control the flow of the program.  This made it easy to add new functionality to the program without having to change the existing code.  For example, if I wanted to add a new message to the Morse code project, I would only need to add a new array containing the  message and I could then simply slot that message into the rotation.

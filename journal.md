### 17 September 2024

Character Description:
Detective Hawk likes to pretend he knows what he is doing, clearly being inspired by watching too much Sherlock Holmes. He usually thinks out loud by talking to his sock puppet ‘Mr. Wright’. He finds clues by sheer luck and makes incorrect assumptions all the time even when it's obvious to the audience. When he interviews the suspects, he asks irrelevant questions. He is just lucky that they slip up.

Detective Hawk rocks a trench coat, mustache, and fedora. He also has a sock puppet sidekick on his hand that he talks to.

![detective_hawk](https://github.com/user-attachments/assets/ab8920c7-f0b4-4344-a60e-056e1bbcd83c)

Construction Considerations:
The sock puppet on his hand should be able to move to simulate talking. The detective's mouth should also be able to move. I think it would be possible using a motor that moves back and forth for the sock puppet. We are currently unsure about how to make the mouth move for the detective.

### 23 September 2024

Rama and I met up in the IM Lab to work on building the base of our robot. We started first by using a ruler and pencil to find the middle of board. ![IMG_4399](https://github.com/user-attachments/assets/8ec5b4ab-6df1-49ff-89f5-e132e0c16d1b)

Then we installed the metal brackets to the motors by following the examples that the other students made. The wheels were also easy to instal to the motor using nuts and bolts from the lab.
![B5BE15A0-204E-409E-9F8F-BD47DE67FB6D](https://github.com/user-attachments/assets/70db8943-af7e-499c-96f9-4f495d43b24b)

Next we started drilling holes into the wooden board to give space for the nuts and bolts. We found this kind of challenging and ran into some small complications (the drill bit snapped in half), but we were able to successfully get it done.
![IMG_4401](https://github.com/user-attachments/assets/39e64f4c-785c-48ee-a3bf-3d8b4b6236c8)

Lastly, we installed the motors with the wheels onto the wooden board with M4 nuts and bolts.![IMG_4403](https://github.com/user-attachments/assets/f9d5e252-15f3-4112-b50e-fe5b5c665feb)

### 26 September 2024

In last Thursday's class, my partner and I focused on refining the wheel setup for our project. Initially, we had two larger wheels attached, and during this session, we worked on adding two smaller wheels. It’s crucial to maintain a bit of wobble in the board to prevent it from getting stuck during the performance. However, the smaller wheels were too short, so we decided to cut small wooden spacers to fit between the wheels and the board, raising the wheels to the right height.

![image](https://github.com/user-attachments/assets/804d6fe7-97d4-4624-8ca7-cb897934d594)

Unfortunately, we miscalculated the length of the wooden spacers, and the board ended up sitting evenly on all four wheels, which eliminated the necessary wobble. To fix this, we removed one of the wheels and replaced the wooden spacer with a smaller piece, creating the imbalance we need.

![image](https://github.com/user-attachments/assets/0e8b38c3-d36e-4716-a315-d7a5e7867e17)

Throughout the process, we used screws to attach everything securely, making pilot and through holes where needed. Looking ahead, our plan for the next class is to add the wires and start the soldering process.

### 1 October 2024
Question's for today's presentations:

Linh's Presentation on Oriza Hirata:
Does the audience knowing they are watching a robot performing or not affect how they emotionally respond to the performance?

Fatima's Presentation on Hiroshi Ishiguro:
What is the need for making realistic humanoid robots, is there any other way to approach robots for entertainment besides looking realistic? It would be cool to make robots look creepy on purpose

### 24 October 2024

This is the final design of our robot, we want to add a motor onto his sock puppet that makes it seem like he is making puppet talk. We also want to add neopixels to his eyes that show where he is looking. The idea is that his eyes will look towards his puppet when talking to him.

![sketch2](https://github.com/user-attachments/assets/7cd6ce0d-0bad-486e-be9b-b49ad70d1331)

### 30 October 2024

Today was focused on finalizing the skeleton of the robot. We added all the main parts to hold up the sock puppet arm. The next thing we tried to do was figure out how to make the jaw move to simulate talking with a servo motor. Unfortunately, we ran into some issues and found out the servo we glued to our pieces of wood is faulty, so our next task is to figure out how to remove the hot glue and replace it with a new motor.

![IMG_4927](https://github.com/user-attachments/assets/50619cd7-f3a1-49f0-854e-4c38a5106924)

### 31 October 2024

Today, we found that the sock puppet's jaw didn't open as wide as we wanted. So we decided to do some prototyping with cardboard to measure the readjusted length we would need for the jaw mechanism. Additionally, we also found that a part of our arduino shield was melted, so we had to resolder the pins. I learnt about how to remove solder from the professor. You have to bang it against the table to knock the solder out of the holes.

### 4 November 2024

My teammate worked on the puppet jaw and used an aluminium piece to extend the jaw more. I found that we actually needed to use a nut and bolt instead of a nail as the piece needed to be as stable as possible, and also worked to instal the servo motor into the bracket at just the right spot and angle where the jaw can extend properly. After lots of trial and error, the jaw was able to open and close.

https://github.com/user-attachments/assets/2caa106a-487a-48f9-9d54-c6069fd1fb32

Next I worked on wiring up all the base components as we still haven't completely wired everything up properly. I looked at others bases and copied the same wiring that others had, then used some tape to keep everything organized and pinned down. After, I soldered the radio onto the Arduino Uno shield to finish off the base.

![WhatsApp Image 2024-11-05 at 00 19 10](https://github.com/user-attachments/assets/94fe8dd7-a317-42ad-8f60-34f610c7dee9)

Next I moved on to completing the Arduino Mega Shield by refering to the lecture notes and the video Github.

![WhatsApp Image 2024-11-05 at 00 19 10 (1)](https://github.com/user-attachments/assets/983b5b05-1181-4df9-92ec-641b49a32543)

As it was past 10 pm in the lab, I wasn't able to access the drills to install the puppet mouth onto the skeleton just yet, so that is the next step. Also, we should use the servo extender cables to wire the puppet to the Arduino Mega Shield

### 5 November 2024

We were able to program the motors at the base so that the robot moved forward.


https://github.com/user-attachments/assets/498a8e98-3a55-4b5f-8d45-6c2040d59ec3


### 7 November 2024

We worked on making the robot be able to work smoothly with the RC controller however we ran into an issue where one of our wheels wasn't able to move in the backwards direction. After lots of troubleshooting, we found that the soldering in one of our boards was the issue using the multimeter. After replacing it with another soldered board it was working smoothly.

![IMG_5026](https://github.com/user-attachments/assets/41353029-8407-47bd-ba2a-406c793e69ee)

### 12 November 2024

We decided we wanted to add a new addition to our robot, a way to simulate his belly laughing as we thought it would be funny if he was constantly laughing unnecessarily. So for today we were working on constructing the mechanism for the stomach. We want to be able to move the stomach up and down, so we constructed a more complex mechanism similar to the jaw mechanism but with more joints. So far we were able to cut up and attach the aluminium parts and also cut the wood we want the servo to rest on.

Additionally, we worked on soldering the transmitter. It was a relatively straight forward proces to make and add all the parts.

![IMG_5055](https://github.com/user-attachments/assets/6fbe1bcd-af5b-4d5a-be02-fe43a2e3814f)
![IMG_5056](https://github.com/user-attachments/assets/f423aaa7-12b4-4cfa-b6bd-b7659b7f8cd7)
![IMG_5057](https://github.com/user-attachments/assets/0194c7df-872a-4d85-94c2-68253058c7f9)

### 13 November 2024

Today we worked on customizing the code given by the professor to ensure a connection was being made by the transmitter. After some small adjustments, a connection was established succesfully. We also did the same for the reciever and it was working successfully.

![IMG_5066](https://github.com/user-attachments/assets/a64bd0b5-ab2b-46cb-a3a0-acf6b7f688a6)
![IMG_5069](https://github.com/user-attachments/assets/a5130488-2602-439e-b0d1-5e80c37ee270)

### 14 November 2024

Today we worked on prototyping the stomach mechanism using hot glue and cardboard. After a lot of trial and error, we found a suitable way to make the mechanism function as we wanted. We will aim to develop this prototype more.

https://github.com/user-attachments/assets/736ec5f9-6c41-4056-bc60-2ac1b89762cb

### 19 November 2024

Today I spent many hours in the lab trying to make the mechanism work. Unfortunately I was having a tough time and the mechanism was not functioning well. I believe this is because a lot of the measurements for the pieces that hold up the mechanism need to be very precise and strong. I think this may be too far out of our scope, we might either need to find another way to simulate the stomach movement or keep iterating.

### 21 November 2024

After consulting with the professor, he said a much easier way to get the same sort of effect is to have a big servo motor connect to a wooden piece that simply turns up and down. This implementation was effective and very easy to implement, I was able to have the servo and piece up on the skeleton by the end of the day with it functioning properly. At the end I stuck the pillow to the wood to create more volume for the detectives large stomach.

https://github.com/user-attachments/assets/18b693a6-2e95-43bf-aa71-cc113aabc8b9

### 28 November 2024

We spent 12 hours straight in the lab working on the robot. During this period we installed the servo eyes and mouth, the costume and accessories, speaker, and ensured the transmitter is properly sending signals so everything is working. I sat through every line and coded the exact movements we wanted for each voiceline, which was many as our character was basically 2 characters in 1. So we had everything done before the long break.

### 6 December 2024

Today we finalized the eyes servo as there were still some issues we had with it not working. We decided to simply use a servo for each eye instead of creating a mechanism where 1 servo can control both eyes at once. The code was also added so that the robot looks at the puppet everytime it speaks.

https://github.com/user-attachments/assets/ff8c1740-36fb-4d6b-bb80-9fa90e856fb5

### 9 December 2024

The costume has been finalized so that the stomach is covered with the shirt and pants, and all the clothes are stuck to the board so it doesn't drape over the wheels. Also the sock puppet got a revamp so that it looks more eccentric and quirky.

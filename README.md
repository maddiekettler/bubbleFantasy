# bubbleFantasy

Project 2 for ARTS 4090: Art & Code & Interactivity at Rensselaer Polytechnic
Institute
Instructor: Shawn Lawson
Code written using the openFrameworks toolkit for C++

## About

In this program, "bubbles" are randomly generated about once every second at the
top of the user's screen. Participants can stand in front of the camera and try
to "pop" the bubbles. Determining whether a bubble is popped or not is based on
movement: the difference between two frames of video are calculated, and if a
bubble overlaps with the movement, it is "popped", or removed from the drawing.

## Inspiration

I was largely inspired by _Text Rain_, an interactive installation by Camille
Utterback and Romy Achituv. In _Text Rain_, falling letters land on anything
darker than a certain threshold and fall when that obstacle is removed. I used a
similar approach with my program.

## In Progress

Progress has been made, as the program more accurately removes the bubbles. I
am struggling, however, as an access violation will get thrown after the program
has run successfully for some time. I am continuing to look into this issue and
trying to figure out why it happens.

I have added sound to my program, so a popping noise will accompany the bubble
as it is popped. As I continue to work on this I would also like to add a drawing
of a popped bubble when the bubble is popped.

## Title

In keeping with the music theme of project names, bubbleFantasy is a (not so good)
play on John Lennon and Yoko Ono's album _Double Fantasy_, originally released 17
November 1980. Lennon would be murdered exactly three weeks later on 8 December
1980.

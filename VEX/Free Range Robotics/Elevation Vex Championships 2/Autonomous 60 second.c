
//First 15 inch
raisetoposition(415);

ejectblocks(600);

stopsucker();
//startejecting();
move(-5,-5);
stop();
stopsucker();
lowerarm();

//Turn Right
move(205,-205);

startsucking();
move(200,200);
moveslow(450,450);
stop();
wait1Msec(1000);

//Turn Right
move(330,-330);

updown = true;
armposition = 320;
StartTask(raisearmtoposition);
findline();

StartTask(followline);
resetencoders();
while(distance() < 300)
{
}
stopsucker();
ejectblocks(50);
startsucking();
while(distance() < 1000)
{
}
while(SensorValue[in12] > 13 || SensorValue[in12] < 10)
{
}
//First 9 inch
StopTask(followline);
stopsucker();
stop();
ejectblocks(550);
move(-15,-15);
updown = false;
armposition = 100;
StartTask(raisearmtoposition);

//Turn Left
move(-205,205);

startsucking();
resetencoders();
moveslow(420,420);
wait1Msec(1000);
move(-300,-300);
move(-335,335);
findline();
updown = true;
armposition = 600;
StartTask(raisearmtoposition);

StartTask(followline);
resetencoders();
while(distance() < 300)
{
}
stopsucker();
ejectblocks(50);
startsucking();
while(distance() < 1000)
{
}

while(SensorValue[in12] > 12 || SensorValue[in12] < 9)
{
}
//First 21 inch
StopTask(followline);
stop();
stopsucker();
ejectblocks(650);
startejecting();
move(-10,-10);
stop();
stopsucker();

lowerarm();
move(185,-185);
startsucking();

moveslow(650,650);
stop();
wait1Msec(1500);
move(280,-280);
move(-30,-30);
updown = true;
armposition = 600;
StartTask(raisearmtoposition);
findline();
StartTask(followline);

resetencoders();
while(distance() < 180)
{
}
stopsucker();
ejectblocks(50);
startsucking();

while(distance() < 500)
{
}
while(SensorValue[in12] > 12 || SensorValue[in12] < 9)
{
}
//Second 21 inch
StopTask(followline);
stop();
stopsucker();
ejectblocks(650);
startejecting();
move(-100,-100);
stop();
stopsucker();
move(-450,450);
move(-10,-10);
findlineturn();
stop();
wait1Msec(300);
exact = true;
StartTask(followline);
updown = false;
armposition = 350;
StartTask(raisearmtoposition);
resetencoders();
while(distance() < 500)
{
}
while(SensorValue[in12] > 58 || SensorValue[in12] < 55)
{
}
StopTask(followline);
move(185,-185);

motor[port1] = 127;
motor[port2] = 127;
wait1Msec(10000);

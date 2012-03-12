	//First 15 inch
raisetoposition(415);
switch(SensorValue[in10])
{
	case 1:
ejectblocks(600);
break;

case 0:
ejectblocks(300);
break;
}
stopsucker();
//startejecting();
move(-5,-5);
stop();
stopsucker();
lowerarm();

switch(SensorValue[in11])
{
	case 1:
//Turn Right
move(205,-205);
break;

	case 0:
//Turn Right
move(-205,205);
break;
}

startsucking();
move(200,200);
moveslow(380,380);
stop();
wait1Msec(1000);

switch(SensorValue[in11])
{
	case 1:
//Turn Right
move(340,-340);
break;

case 0:
//Turn Right
move(-340,340);
break;
}

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

switch(SensorValue[in11])
{
	case 1:
//Turn Left
move(-195,195);
break;

	case 0:
//Turn Left
move(195,-195);
break;
}

startsucking();
resetencoders();
move(370,370);
stop();
wait1Msec(50000);

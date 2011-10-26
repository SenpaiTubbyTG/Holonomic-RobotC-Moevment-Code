typedef struct{
int enabled;
int error;
int errorLast;
int errorTotal;
int selectedValue;
int Kp;
int Ki;
int Kd;
int output;
int input;
int maxOut;
int minOut;
int maxIn;
int minIn;
int maxError;
int inputSensorIndex;
int outputMotorIndex;
int result;
}controller;

void init(controller PID)
{
 // init (PID);
  PID.errorLast = 0;
  PID.errorTotal = 0;
  PID.Kp = 0;
  PID.Ki = 0;
  PID.Kd = 0;
  PID.enabled = 0;
  PID.maxOut = 127;
  PID.minOut = -127;
  PID.maxIn = 0;
  PID.minIn = 0;
  PID.maxError = 0;
  PID.enabled = 0;
}
void init(controller PID, int out, int in)
{
  init (PID);
  PID.output = out;
  PID.input = in;
}

void init(controller PID, int input)
{
  init(PID);
  PID.inputSensorIndex = input;
}
void init(controller PID, int output)
{
  init(PID);
  PID.outputMotorIndex = output;
}
void init(controller PID, int input, int output)
{
  init(PID);
  PID.inputSensorIndex = input;
  PID.outputMotorIndex = output;
}
void setMaxError(controller PID, int max)
{
  if(max >= 0)
  PID.maxError = max;
}
void setKp(controller PID, int k)
{
  init(PID);
  PID.Kp = k;
}
void setKi(controller PID, int k)
{
  init(PID);
  PID.Ki = k;
}
void setKd(controller PID, int k)
{
  init(PID);
  PID.Kd = k;
}
void enable(controller PID)
{
  init(PID);
  PID.enabled = 1;
}
void disable(controller PID)
{
  init(PID);
  PID.enabled = 0;
}
bool onTarget(controller PID)
{
  int error= (abs(PID.selectedValue - SensorValue[PID.inputSensorIndex]);
  if (error <= PID.maxError)
    return true;
  else
    return false;
}
void setSetpoint(controller PID, int newSetpoint)
{
  PID.selectedValue = newSetpoint;
}
void setPIDs(controller PID, int kp, int ki, int kd)
{
  PID.Kp = kp;
  PID.Ki = ki;
  PID.Kd = kd;
}

int calcPID(controller PID)
{
if(PID.enabled)
{
  PID.input = SensorValue[PID.inputSensorIndex];
  //PID.errorLast = PID.error;
  PID.error = PID.selectedValue - PID.input;
  if(abs(PID.error) > (PID.maxIn - PID.minIn)/2)
  {
    if(PID.error > 0)
    {
      PID.error = PID.error - PID.maxIn + PID.minIn;
    }
    else
    {
      PID.error = PID.error + PID.maxIn - PID.minIn;
    }
  }
  if (((PID.errorTotal + PID.errorTotal) * PID.Ki < PID.maxOut)
    &&((PID.errorTotal + PID.error) * PID.Ki > PID.minOut))
  {
    PID.errorTotal += PID.error;
  }
  PID.result = (PID.error / PID.Kp +
  PID.errorTotal / PID.Ki +
  (PID.error - PID.errorLast) / PID.Kd);
  PID.errorLast = PID.error;

  if (PID.result > PID.maxOut)
    {
      PID.result = PID.maxOut;}
      else if (PID.result < PID.minOut)
        {
          PID.result = PID.minOut;
        }
  return PID.result;
}

else
  return 0;
}

int targetarmposition;
int liftperror;
int liftderror;
int oldliftperror;
int turnamount;
int programselect = 1;
int currentspeed;
int targetspeed;
int power;
int spinamount;
int targetspeedL;
int targetspeedR;
int distance;
int leftencoderstore;
int rightencoderstore;

bool bossenabled = false;
bool descoreup = true;
bool armraising = false;
bool redteam = true;
bool programselecting = true;

const int trim = 10;
const int lowerlimit = 675;
const int basefromup = 420;
const int basefromdown = 450;
const int wallgoalheight = 360;
const int descoreheight = 645;
const int stackheight = 510;
const int armmax = 190;
const int quarter = 300;
// int threshold = 600;

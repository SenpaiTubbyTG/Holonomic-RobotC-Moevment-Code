void autonFilter() {
    if (redteam == true)
    if (programselect == 1)  {
    Red_Program = 1;
  }

    if (redteam == true)
    if (programselect == 2)  {
    Red_Program = 2;
  }

    if (redteam == true)
    if (programselect == 3)  {
    Red_Program = 3;
  }

    if (redteam == false)
    if (programselect == 1)  {
    Blue_Program = 1;
  }

    if (redteam == false)
    if (programselect == 2)  {
    Blue_Program = 2;
  }

    if (redteam == false)
    if (programselect == 3)  {
    Blue_Program = 3;
  }

///////////////////////////////////////////////////////////////////////////////////////////////
  {
    if(Red_Program == 1)
    {
      autonIntHighLow();
    }
    else if(Red_Program ==2)
    {
      autonIntHighLow();
    }
    else if(Red_Program ==3)
    {
      autonIntHighLow();
    }
    else if (Blue_Program ==  1)
    {
      autonIntHighLow();
    }
    else if(Blue_Program == 2)
    {
      autonIntHighLow();
    }
    else if(Blue_Program == 3)
    {
      autonIntHighLow();
    }

  }// end bracket set
}// end autonFilter

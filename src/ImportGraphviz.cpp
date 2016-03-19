/*
Copyright (C) 2000,2001 Stefan Duffner 

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/


//#include "Options.h"
//#include "Import.h"
#ifdef GRAPHVIZ_FOUND
#ifdef WIN32
  #include <gvc.h>
  //#include <graph.h>
#else
  #include <gvc.h>
  //#include <graph.h>
#endif
  #include "TransitionInfoBin.h"
  #include "TransitionInfoASCII.h"
  #include "TransitionInfoText.h"
#endif

#ifdef WIN32
//math.h extensions not defined under Windows
/* Constants rounded for 21 decimals. */
#define M_E 2.71828182845904523536
#define M_LOG2E 1.44269504088896340736
#define M_LOG10E 0.434294481903251827651
#define M_LN2 0.693147180559945309417
#define M_LN10 2.30258509299404568402
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define M_PI_4 0.785398163397448309616
#define M_1_PI 0.318309886183790671538
#define M_2_PI 0.636619772367581343076
#define M_1_SQRTPI 0.564189583547756286948
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2 1.41421356237309504880
#define M_SQRT_2 0.707106781186547524401
#endif

#include "Machine.h"
#include "ImportGraphviz.h"

#define maxpoints 30


ImportGraphviz::ImportGraphviz(Options* opt)
  	  : Import(opt)
{
}


/*
ImportGraphviz::~ImportGraphviz()
{
}
*/


Project* ImportGraphviz::doImport()
{
#ifndef GRAPHVIZ_FOUND
  return NULL;
#else
  //project->addMachine("tmp", "1.0", "S.D.", 2, 2, 3,  
  Machine* m = new Machine(project);
  project->addMachine(m);

  //aginit();
  FILE* fd = fopen(fileName, "r");
  if (!fd)
    return NULL;

  Agraph_t* G;
  GVC_t *gvc;
  Agnode_t* node;
  Agedge_t* edge;
  char* lab;
  QString label,labelin, labelout, insub;
  int mtype = -1;
  QRect bb;
  float maxsizex, maxsizey;
  float dpi;
  int graph_offsetx = 120;
  int graph_offsety = 50;
  const char infosep[] = "###";

  gvc = gvContext();
  G = agread(fd, 0);
  //G = agread(fd);

  // check if it is a directed graph
  //if (!G || !AG_IS_DIRECTED(G))
  if (!G) // || !((G)->kind & AGFLAG_DIRECTED)
  {
    gvFreeContext(gvc);
    agclose(G);
    fclose(fd);
    return NULL;;
  }

  gvLayout(gvc, G, "dot");
  //gvRender(gvc, G, "plain", NULL);
  attach_attrs(G);

  // set bounding box
  lab = agget(G, (char*)"bb");
  if (lab && strcmp(lab,"\\N"))
    label = QString(lab);
  else
    label="";
  QStringList bbl=label.split(",");
  bb.setCoords((int)bbl.at(0).toFloat(),(int)bbl.at(1).toFloat(),(int)bbl.at(2).toFloat(),(int)bbl.at(3).toFloat());

  // determine maximum graph size (in inches)
  lab = agget(G, (char*)"size");
  if (lab && strcmp(lab,"\\N"))
    label = QString(lab);
  else
    label="";
  maxsizex = label.section(",",1,1).toFloat();
  maxsizey = label.section(",",2,2).toFloat();

  lab = agget(G, (char*)"dpi");
  if (lab && strcmp(lab,"\\N"))
    label = QString(lab);
  else
    label="72";
  dpi = label.toFloat();

  // guess machine type
  int mtype_final=-1;
  int prev_mtype=-1;
  int guess_count=0;
  for (node = agfstnode(G); node && /*mtype_final==-1*/guess_count<=10; node = agnxtnode(G,node))
    for (edge = agfstout(G,node); edge; edge = agnxtout(G,edge))
    {
      lab = agget(edge, (char*)"label");
      if (lab && strcmp(lab,"\\N"))
	label = QString(lab);
      else
	label="";
      //printf("label: %s\n", label);
      labelin = label.section(infosep, 0, 0);
      labelout = label.section(infosep, 1, 1);
      mtype = IOInfo::guessType(labelin);
      /*
      if (mtype!=-1)
	break;
	*/
      if (mtype>mtype_final)
	mtype_final = mtype;  // choose most general type
      guess_count++;
      if (guess_count>10)
	break;
      prev_mtype=mtype;
    }
    if (mtype_final==-1)  // if guess is unsucessful assume it's ASCII
      m->setType(1);
    else
      m->setType(mtype_final);
  /*
  qDebug("Machine type: %d", mtype);
  qDebug("Machine name: %s", G->name);
  */
  m->setName(agnameof(G));

  // determine number of inputs and outputs
  int numin=0, numout=0, nummoore=0;
  if (mtype==0)
  {
    for (node = agfstnode(G); node; node = agnxtnode(G,node))
    {
      for (edge = agfstout(G,node); edge; edge = agnxtout(G,edge))
      {
	lab = agget(edge, (char*)"label");
	if (lab && strcmp(lab,"\\N"))
	  label = QString(lab);
	else
	  label="";
	//printf("label: %s\n", label);
	labelin = label.section(infosep, 0, 0);
	labelout = label.section(infosep, 1, 1);

	labelin.replace("NOT","");
	labelin.replace("ANY","");
	labelin.replace("DEF","");
	labelin.replace(" ","");
	/*
	qDebug(labelin);
	qDebug(labelout);
	*/
	QStringList sl = labelin.split("|");
	for(int i=0; i<sl.size();++i)
	{
          insub = sl.at(i);
	  if (insub.length()>numin)
	    numin=insub.length();
	}
	labelout.replace(" ","");
	if (labelout.length()>numout)
	  numout=labelout.length();
      }
      lab = agget(node, (char*)"label");
      if (lab && strcmp(lab,"\\N"))
      {
	label = QString(lab);
	if (label.contains(infosep))
	{
	  labelin = label.section(infosep, 0, 0);
	  labelout = label.section(infosep, 1, 1);
	  labelout.replace(" ","");
	  /*
	  qDebug(labelin);
	  qDebug(labelout);
	  */
          if (labelout.length()>nummoore)
	    nummoore=labelout.length();
	}
      }
    }
  }
  else if (mtype==1)
  {
    numin = 8;
    numout = 8;
    nummoore = 8;
  }
  else
  {
    numin = 8;
    numout = 8;
    nummoore = 0;
  }
  m->setNumInputs(numin);
  m->setMealyInputNames(numin, "");
  m->setNumOutputs(numout);
  m->setMealyOutputNames(numout, "");
  m->setNumMooreOutputs(nummoore);
  m->setMooreOutputNames(nummoore, "");
  /*
  qDebug("# inputs: %d", numin);
  qDebug("# outputs: %d", numout);
  qDebug("# moore outputs: %d", nummoore);
  */


  // create nodes
  bool endstate;
  float nwidthf;
  int nwidth;
  float xpos, ypos;
  QString nname, mooreout="";
  for (node = agfstnode(G); node; node = agnxtnode(G,node))
  {
    // try to get node name from label
    mooreout="";
    nname="";
    lab = agget(node, (char*)"label");
    if (lab && strcmp(lab,"\\N"))
      nname = QString(lab);
    else
      nname = agnameof(node);
    if (mtype==0)
    {
      lab = agget(node, (char*)"moore");
      if (lab && strcmp(lab,"\\N"))
	mooreout = QString(lab);
    }
    IOInfo* nmoore = new IOInfoBin(IO_MooreOut,mooreout);

    // endstate ?
    lab = agget(node, (char*)"shape");
    if (!strcmp(lab,"doublecircle"))
      endstate=1;
    else 
      endstate=0;

    // circle width / radius
    lab = agget(node, (char*)"width");
    if (lab && strcmp(lab,"\\N"))
    {
      label = QString(lab);
      nwidthf = label.toFloat();
      nwidthf *= dpi;
      nwidth = int(nwidthf+.5);
    }
    else
      nwidth = 80;

    //qDebug("dpi: %f", dpi);
    //qDebug("node width: %f", nwidthf);


    //printf("get returned: %s\n", agget(node, (char*)"pos"));
    QString label(agget(node, (char*)"pos"));
    xpos = label.section(",",0,0).toFloat();
    ypos = bb.height()-label.section(",",1,1).toFloat();
    QPen pen(QColor(0,0,0));
    pen.setWidth(1);
    m->addState(nname, "", 0, nmoore, xpos+graph_offsetx, ypos+graph_offsety, (int)(nwidth/2.0), 1.0, pen, endstate);
  }

  // create transitions
  //QList<GState*> slist = m->getSList();
  GState* cur_state, *end_state;
  int scount=0;
  QString sti;
  double tx[maxpoints], ty[maxpoints], cpx[4], cpy[4];
  double stx[maxpoints], sty[maxpoints];
  double tmpx, tmpy;
  QString enname;
  double straight_thresh=M_PI/100;
  bool straight;

  for (node = agfstnode(G); node; node = agnxtnode(G,node))
  {
    nname="";
    lab = agget(node, (char*)"label");
    if (lab && strcmp(lab,"\\N"))
      nname = QString(lab);
    else
      nname = agnameof(node);
    cur_state = m->getState(nname);
    if (cur_state)
    {
      for (edge = agfstout(G,node); edge; edge = agnxtout(G,edge))
      {
	// get name of end state
	enname="";
	lab = agget(aghead(edge), (char*)"label");
	if (lab && strcmp(lab,"\\N"))
	  enname = QString(lab);
	else
	  enname = agnameof(aghead(edge));
	//qDebug("%s -> %s", nname.toLatin1().constData(), enname.toLatin1().constData());

	end_state = m->getState(enname);

	// create transition info (transition condition)
	TransitionInfo* ti; 
	switch (mtype)
	{
	  case 0:
	    ti = new TransitionInfoBin();
	    break;
	  case 1:
	    ti = new TransitionInfoASCII();
	    break;
	  default:
	    ti = new TransitionInfoText();
	    break;
	}
	labelin = "";
	labelout = "";
	lab = agget(edge, (char*)"label");
	if (lab && strcmp(lab,"\\N"))
	{
	  label = QString(lab);
	  if (label.contains(infosep))
	  {
	    labelin = label.section(infosep, 0, 0);
	    labelout = label.section(infosep, 1, 1);
	  }
	  else
	    labelin = label;
	}
	if (labelin.contains("ANY"))
	{
	  ti->getInputInfo()->setAnyInput(true);
	  labelin="";
	}
	if (labelin.contains("DEF"))
	{
	  ti->getInputInfo()->setDefault(true);
	  labelin="";
	}
	if (labelin.contains("NOT"))
	{
	  ti->getInputInfo()->setInvert(true);
	  labelin.replace("NOT","");
	  labelin.replace("NOT ","");
	}
	ti->setInputs(labelin, numin);
	ti->setOutputs(labelout, numout);

	// get transition position
	lab = agget(edge, (char*)"pos");
	if (lab)
	  label = QString(lab);
	else 
	  label = "";
	QStringList sl = label.split(" ");
	int sllen = sl.length();
	//qDebug("len %d", sllen);
	int ind=0;
	int eind=-1;
	int cpind, cpnum=0;  // cpnum holds the number of control points stored in stx, sty
	for(int i=0;i<sllen; i++)
	{
	  if (sl.at(i).section(",",0,0)=="e")
	  {
	    eind = i;
	    ypos = sl.at(i).section(",",-1,-1).toFloat();
	    xpos = sl.at(i).section(",",-2,-2).toFloat();
	    tmpx=xpos+graph_offsetx;
	    tmpy=bb.height()-ypos+graph_offsety;
	  }
	  else if (sllen!=5) //if (sllen==5 || (ind%3)==0)
	  {
	    // If we have 5 control points we can map the spline directly to a cubic spline. 
	    // Otherwise we store all control points in stx, sty
	    //qDebug("control point %d", i);
	    stx[cpnum] = sl.at(i).section(",",-2,-2).toFloat()+graph_offsetx;
	    sty[cpnum] = bb.height()-sl.at(i).section(",",-1,-1).toFloat()+graph_offsety;
	    //qDebug("%f %f   %f %f", sl.at(i).section(",",-1,-1).toFloat(), sl.at(i).section(",",-2,-2).toFloat(), tx[cpnum], ty[cpnum]);
	    ind++;
	    cpnum++;
	  }
	  else
	    ind++;
	}
	if (eind>=0)
	{
	  if (sllen>5)
	  {
	    stx[cpnum] = tmpx;
	    sty[cpnum] = tmpy;
	    cpnum++;
	  }
	}
	//qDebug("cpnum: %d", cpnum);

	if (sllen==5)
	{
	  // For 5 control points: direct mapping to cubic spline (while leaving out second last point)
	  ind=0;
	  for(int i=0; i<5; i++)
	  {
	    if (i==eind)
	      continue;
	    cpx[ind] = sl.at(i).section(",",-2,-2).toFloat()+graph_offsetx;
	    cpy[ind] = bb.height()-sl.at(i).section(",",-1,-1).toFloat()+graph_offsety;
	    ind++;
	  }
	  if (eind>=0)
	  {
	    cpx[3] = tmpx;
	    cpy[3] = tmpy;
	  }
	  // Check if it is a straight line segment
	  double mainangle;
	  if (cpx[3]-cpx[0]!=0)
	    mainangle = atan((cpy[0]-cpy[3])/(cpx[3]-cpx[0]));
	  else
	    mainangle = M_PI_2;
	  double angle1, angle2;
	  if (cpx[1]-cpx[0]!=0)
	    angle1 = atan((cpy[0]-cpy[1])/(cpx[1]-cpx[0]));
	  else
	    angle1 = M_PI_2;
	  if (cpx[3]-cpx[2]!=0)
	    angle2 = atan((cpy[2]-cpy[3])/(cpx[3]-cpx[2]));
	  else
	    angle2 = M_PI_2;
	  if (fabs(angle1-mainangle)<straight_thresh && fabs(angle2-mainangle)<straight_thresh)
	  {
	    straight=true;
	    //qDebug("straight");
	    cpx[1] = cpx[0] + 0.3*(cpx[3]-cpx[0]);
	    cpy[1] = cpy[0] + 0.3*(cpy[3]-cpy[0]);
	    cpx[2] = cpx[3] - 0.3*(cpx[3]-cpx[0]);
	    cpy[2] = cpy[3] - 0.3*(cpy[3]-cpy[0]);
	  }
	  else
	  {
	    if (cur_state==end_state)
	      straight=true;
	    else
	      straight=false;
	  }
	}
	else
	{
	  // For more than 5 control points, they are all stored in stx, sty 
	  // and we have to approximate the spline segments with a single cubic spline
	  tx[0] = stx[0];
	  ty[0] = sty[0];
	  tx[maxpoints-1] = tmpx;
	  ty[maxpoints-1] = tmpy;
	  // Fist check if it is a straight line segment
	  int c1ind, c2ind;
	  c1ind = cpnum/3;
	  c2ind = 2*cpnum/3-3;
	  cpx[0] = stx[0]; cpy[0] = sty[0];
	  cpy[0] = sty[0]; cpy[0] = sty[0];
	  cpx[1] = stx[c1ind]; cpy[1] = sty[c1ind];
	  cpy[1] = sty[c1ind]; cpy[1] = sty[c1ind];
	  cpx[2] = stx[c2ind]; cpy[2] = sty[c2ind];
	  cpy[2] = sty[c2ind]; cpy[2] = sty[c2ind];
	  cpx[3] = stx[cpnum-1]; cpy[3] = sty[cpnum-1];
	  cpy[3] = sty[cpnum-1]; cpy[3] = sty[cpnum-1];
	  double mainangle;
	  if (cpx[3]-cpx[0]!=0)
	    mainangle = atan((cpy[0]-cpy[3])/(cpx[3]-cpx[0]));
	  else
	    mainangle = M_PI_2;
	  double angle1, angle2;
	  if (cpx[1]-cpx[0]!=0)
	    angle1 = atan((cpy[0]-cpy[1])/(cpx[1]-cpx[0]));
	  else
	    angle1 = M_PI_2;
	  if (cpx[3]-cpx[2]!=0)
	    angle2 = atan((cpy[2]-cpy[3])/(cpx[3]-cpx[2]));
	  else
	    angle2 = M_PI_2;
	  if (fabs(angle1-mainangle)<straight_thresh && fabs(angle2-mainangle)<straight_thresh)
	  {
	    straight=true;
	    //qDebug("straight");
	    cpx[1] = cpx[0] + 0.3*(cpx[3]-cpx[0]);
	    cpy[1] = cpy[0] + 0.3*(cpy[3]-cpy[0]);
	    cpx[2] = cpx[3] - 0.3*(cpx[3]-cpx[0]);
	    cpy[2] = cpy[3] - 0.3*(cpy[3]-cpy[0]);
	  }
	  else
	  {
	    if (cur_state==end_state)
	    {
	      double sxpos, sypos;
              cur_state->getPos(sxpos, sypos);
              cur_state->calcLoop(sxpos, sypos, cur_state->getRadius(), cpx[0], cpy[0], cpx[1], cpy[1], cpx[2], cpy[2]);
	      straight=true;
	    }
	    else
	    {
	      straight=false;

	      // generate data points (uniformly on spline segments)
	      int nsplines = cpnum/3;
	      float* slength = new float[nsplines]; // approximate length of splines
	      float* cumlen = new float[nsplines]; // accumulative length of splines
	      float sumlen=0;
	      memset(slength, 0, nsplines*sizeof(float));
	      float t;
	      float dx, dy;
	      for(int si=0; si<nsplines; si++)
	      {
		dx = stx[(si+1)*3]-stx[si*3];
		dy = sty[(si+1)*3]-sty[si*3];
		slength[si] = sqrt(dx*dx+dy*dy);
		sumlen += slength[si];
	      }
	      cumlen[0]=slength[0]/sumlen;
	      for(int si=1; si<nsplines; si++)
		cumlen[si]=cumlen[si-1]+slength[si]/sumlen;

	      int curspline=0;
	      float lastind=0;
	      float oneminust;
	      for(int di=0; di<maxpoints-1; di++)
	      {
		if ((float)di/maxpoints>cumlen[curspline] && curspline<nsplines-1)
		{
		  lastind=maxpoints*cumlen[curspline];
		  if (lastind<0)
		    lastind=0;
		  curspline++;
		}
		t = float(di-lastind)/(maxpoints*(slength[curspline]/sumlen));
		if (t>1)
		  t=1;

		oneminust = 1.0-t;
		tx[di] = oneminust*oneminust*oneminust * stx[curspline*3] + 3*oneminust*oneminust*t*stx[curspline*3+1] + 3*oneminust*t*t*stx[curspline*3+2] + t*t*t*stx[curspline*3+3];
		ty[di] = oneminust*oneminust*oneminust * sty[curspline*3] + 3*oneminust*oneminust*t*sty[curspline*3+1] + 3*oneminust*t*t*sty[curspline*3+2] + t*t*t*sty[curspline*3+3];
		/*
		qDebug("%f  %f", tx[di], ty[di]);
		if (di>0)
		{
		  qDebug("           dist %f", sqrt((tx[di]-tx[di-1])*(tx[di]-tx[di-1])+(ty[di]-ty[di-1])*(ty[di]-ty[di-1])));
		}
		*/
	      }

	      cubicSplineApprox(maxpoints, tx, ty, cpx, cpy);
	      delete [] slength;
	      delete [] cumlen;
	    }
	  }
	}
        cur_state->addTransition(project, end_state, ti, cpx[0], cpy[0], cpx[3], cpy[3], cpx[1], cpy[1], cpx[2], cpy[2], "", straight, false);
      }
    }
    scount++;
  }

  gvFreeLayout(gvc, G);
  agclose(G);
  gvFreeContext(gvc);

  fclose(fd);

  return project;
#endif
}





void ImportGraphviz::cubicSplineApprox(int numin, double x[], double y[], double cpx[], double cpy[])
{
  //qDebug("cubic spline approximation with %d points", numin);
  
  const double lrate = 0.1;
  double ax, bx, cx, dx, ay, by, cy, dy;
  bool convergence=false;
  int curind=0;
  double curt, mx, my, tmpmx, tmpmy;
  double mindist, dist, distx, disty;
  double errx, erry, denom;
  double err_diff, cur_err=10, prev_err, avg_err_diff=10;
  int niter=0;
  double newcx1, newcy1, newcx2, newcy2;

  // initialise spline
  cpx[0] = x[0];
  cpy[0] = y[0];
  cpx[3] = x[numin-1];
  cpy[3] = y[numin-1];
  if (numin<=5)
  {
    cpx[1] = cpx[0]+0.3*(cpx[3]-cpx[0]);
    cpy[1] = cpy[0]+0.3*(cpy[3]-cpy[0]);
    cpx[2] = cpx[3]-0.3*(cpx[3]-cpx[0]);
    cpy[2] = cpy[3]-0.3*(cpy[3]-cpy[0]);
  }
  else
  {
    cpx[1] = x[numin/3];
    cpy[1] = y[numin/3];
    cpx[2] = x[2*numin/3];
    cpy[2] = y[2*numin/3];
  }

  double mainangle;
  if (cpx[3]-cpx[0]!=0)
    mainangle = atan((cpy[0]-cpy[3])/(cpx[3]-cpx[0]));
  else
    mainangle = M_PI_2;
  if (cpx[3]<cpx[0])
    mainangle += M_PI;
  double maindist = sqrt((cpx[0]-cpx[3])*(cpx[0]-cpx[3])+(cpy[0]-cpy[3])*(cpy[0]-cpy[3]));;

  //qDebug("angle: %f", mainangle);
  float distc1, distc2;
  float angle1, angle2;
  /*
  cpx[1] = x[1];
  cpy[1] = y[1];
  cpx[2] = x[numin-2];
  cpy[2] = y[numin-2];
  */

  // stochastic gradient descent cycling through all data points
  curind=1;
  while (!convergence)
  {
    // current model parameters
    ax = -cpx[0] + 3*cpx[1] - 3*cpx[2] + cpx[3];
    bx = 3*cpx[0] - 6* cpx[1] + 3*cpx[2];
    cx = (-3)*cpx[0] + 3*cpx[1];
    dx = cpx[0];
    ay = -cpy[0] + 3*cpy[1] - 3*cpy[2] + cpy[3];
    by = 3*cpy[0] - 6* cpy[1] + 3*cpy[2];
    cy = (-3)*cpy[0] + 3*cpy[1];
    dy = cpy[0];

    // find t for which model is closest to current data point
    mindist=10e8;
    float t, t1, t2;
    float searchintervall;
    float tmpmx1, tmpmx2, tmpmy1, tmpmy2;
    float dist1, dist2;
    for(t=0.0; t<=1; t+=0.1)
    {
      tmpmx = ax*t*t*t + bx*t*t + cx*t + dx;
      tmpmy = ay*t*t*t + by*t*t + cy*t + dy;
      distx = tmpmx-x[curind];
      disty = tmpmy-y[curind];
      dist = sqrt(distx*distx+disty*disty);
      if (dist<mindist)
      {
	mindist=dist;
	curt=t;
	mx = tmpmx;
	my = tmpmy;
      }
    }
    searchintervall=0.05;
    for(int i=0; i<10; i++)
    {
      t1 = curt-searchintervall;
      t2 = curt+searchintervall;
      tmpmx1 = ax*t1*t1*t1 + bx*t1*t1 + cx*t1 + dx;
      tmpmy1 = ay*t1*t1*t1 + by*t1*t1 + cy*t1 + dy;
      tmpmx2 = ax*t2*t2*t2 + bx*t2*t2 + cx*t2 + dx;
      tmpmy2 = ay*t2*t2*t2 + by*t2*t2 + cy*t2 + dy;
      distx = tmpmx1-x[curind];
      disty = tmpmy1-y[curind];
      dist1 = sqrt(distx*distx+disty*disty);
      distx = tmpmx2-x[curind];
      disty = tmpmy2-y[curind];
      dist2 = sqrt(distx*distx+disty*disty);
      if (dist1<mindist)
      {
	mindist=dist1;
	curt=t1;
	mx = tmpmx1;
	my = tmpmy1;
      }
      else if (dist2<mindist)
      {
	mindist=dist2;
	curt=t2;
	mx = tmpmx2;
	my = tmpmy2;
      }
      searchintervall/=2;
    }
    // adjust model parameters (gradient descent)
    errx = x[curind]-mx;
    erry = y[curind]-my;
    denom = 1.0; //sqrt(errx*errx+erry*erry);
    ax = ax + lrate * curt*curt*curt * errx/denom;
    bx = bx + lrate * curt*curt * errx/denom;
    cx = cx + lrate * curt * errx/denom;
    dx = dx + lrate * errx/denom;
    ay = ay + lrate * curt*curt*curt * erry/denom;
    by = by + lrate * curt*curt * erry/denom;
    cy = cy + lrate * curt * erry/denom;
    dy = dy + lrate * erry/denom;

    // only adjust middle control points and keep end points fixed
    newcx1 = 1.0/3.0*cx + dx;
    newcy1 = 1.0/3.0*cy + dy;
    newcx2 = 1.0/3.0*bx + 2.0/3.0*cx + dx;
    newcy2 = 1.0/3.0*by + 2.0/3.0*cy + dy;

    distc1 = sqrt((newcx1-cpx[0])*(newcx1-cpx[0])+(newcy1-cpy[0])*(newcy1-cpy[0]));
    distc2 = sqrt((newcx2-cpx[3])*(newcx2-cpx[3])+(newcy2-cpy[3])*(newcy2-cpy[3]));
    if (cpx[3]-newcx2!=0)
      angle2 = atan((newcy2-cpy[3])/(cpx[3]-newcx2));
    else
      angle2 = M_PI_2;
    if (cpx[3]<newcx2)
      angle2 += M_PI;
    if (cpx[0]-newcx1!=0)
      angle1 = atan((cpy[0]-newcx1)/(newcx1-cpx[0]));
    else
      angle1 = M_PI_2;
    if (newcx1<cpx[0])
      angle1 += M_PI;

    if (distc1>0.2*maindist && distc1<0.8*maindist && fabs(angle1-mainangle)<M_PI)
    {
      if (newcx1>0)
	cpx[1] = newcx1;
      if (newcy1>0)
	cpy[1] = newcy1;
    }
    if (distc2>0.2*maindist && distc2<0.8*maindist && fabs(angle2-mainangle)<M_PI_2)
    {
      if (newcx2>0)
	cpx[2] = newcx2;
      if (newcy2>0)
	cpy[2] = newcy2;
    }

    curind++;
    //curind = ((curind-1)%(numin-2))+1; // don't include start and end point
    curind = curind%numin;

    niter++;

    prev_err = cur_err;
    cur_err = sqrt(errx*errx+erry*erry);
    err_diff = fabs(prev_err-cur_err);

    avg_err_diff = 0.95 * avg_err_diff + 0.05 * err_diff;
    //qDebug("curr_err %f   avg_err_diff: %f", cur_err, avg_err_diff);
    convergence = (niter>10 && avg_err_diff < 0.1) || niter>200;;
  }
  //qDebug("converged after %d iterations", niter);
}





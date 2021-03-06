//=========================================================
//  OOMidi
//  OpenOctave Midi and Audio Editor
//    $Id: helper.cpp,v 1.1.1.1 2003/10/27 18:51:27 wschweer Exp $
//  (C) Copyright 2003 Werner Schweer (ws@seh.de)
//=========================================================

#include "helper.h"

extern bool hIsB;
static const char* vall[] = {
	"c", "c#", "d", "d#", "e", "f", "f#", "g", "g#", "a", "a#", "h"
};
static const char* valu[] = {
	"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "H"
};

//---------------------------------------------------------
//   pitch2string
//---------------------------------------------------------

QString pitch2string(int v)
{
	if (v < 0 || v > 127)
		return QString("----");
	int octave = (v / 12) - 2;
	QString o;
	o.sprintf("%d", octave);
	int i = v % 12;
	QString s(octave < 0 ? valu[i] : vall[i]);
	if (hIsB)
	{
		if (s == "h")
			s = "b";
		else if (s == "H")
			s = "B";
	}
	return s + o;
}



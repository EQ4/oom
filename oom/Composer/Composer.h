//=========================================================
//  OOMidi
//  OpenOctave Midi and Audio Editor
//    $Id: Composer.h,v 1.17.2.15 2009/11/14 03:37:48 terminator356 Exp $
//  (C) Copyright 1999 Werner Schweer (ws@seh.de)
//=========================================================

#ifndef __COMPOSER_H__
#define __COMPOSER_H__

#include <vector>

#include "AbstractMidiEditor.h"
#include "ComposerCanvas.h"
//#include "trackautomationview.h"

class QAction;
class QCheckBox;
class QMainWindow;
class QMenu;
class QScrollArea;
class QScrollBar;
class QToolButton;
class QWheelEvent;
class QKeyEvent;
class QComboBox;
class QStackedWidget;
class QVBoxLayout;

class ScrollScale;
class MTScale;
class Track;
class Xml;
class Splitter;
class LabelCombo;
class PosLabel;
class Conductor;
class AudioStrip;
class Strip;
class SpinBox;
class TrackViewDock;
class RouteMapDock;
class CommentDock;
class CItem;
class HeaderList;
class EditToolBar;

static const int MIN_HEADER_WIDTH = 240;
static const int MAX_HEADER_WIDTH = 400;

//---------------------------------------------------------
//   Composer
//---------------------------------------------------------

class Composer : public QWidget
{
    Q_OBJECT

    int _quant, _raster;
    ComposerCanvas* canvas;
    ScrollScale* hscroll;
    QScrollBar* vscroll;
	HeaderList* m_trackheader;
    MTScale* time;
    SpinBox* lenEntry;
    bool showTrackinfoFlag;
    Conductor* midiConductor;
	QScrollArea *infoScroll;
	QScrollArea *listScroll;
	QScrollArea *mixerScroll;
    AudioStrip* waveTrackInfo;
	EditToolBar *edittools;

    Track* selected;

    LabelCombo* typeBox;
    QToolButton* ib;
    int trackInfoType;
    Splitter* split;
    int songType;
    PosLabel* cursorPos;
    SpinBox* globalTempoSpinBox;
    SpinBox* globalPitchSpinBox;
	QTabWidget* _rtabs;
	Strip* _lastStrip;
	TrackViewDock* _tvdock;
	RouteMapDock* _rmdock;
	CommentDock* _commentdock;
	QWidget *central;
	QVBoxLayout *mlayout;
    QList<Strip* > m_strips;

    unsigned cursVal;
    void genTrackInfo(QWidget* parent);
    void genMidiTrackInfo();
    void genWaveTrackInfo();
    void switchInfo(int);
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void songlenChanged(int);
    void showTrackInfo(bool);
    void trackSelectionChanged();
    void trackInfoScroll(int);
    void songChanged(int);
    void modeChange(int);
    void setTime(unsigned);
    void globalPitchChanged(int);
    void globalTempoChanged(int);
    void setTempo50();
    void setTempo100();
    void setTempo200();
    //void seek();
	void splitterMoved(int, int);
	void resourceDockAreaChanged(Qt::DockWidgetArea);
	void currentTabChanged(int);

signals:
    void redirectWheelEvent(QWheelEvent*);
    void editPart(Track*);
    void selectionChanged();
    void dropSongFile(const QString&);
    void dropMidiFile(const QString&);
    void startEditor(PartList*, int);
    void toolChanged(int);
    void updateHeaderTool(int);
    void updateFooterTool(int);
    //void addMarker(int);
    void setUsedTool(int);


protected:
    virtual void wheelEvent(QWheelEvent* e);

public slots:
    void dclickPart(Track*);
    void setTool(int);
    void updateConductor(int flags);
    void configChanged();
    void controllerChanged(Track *t);
    void showTrackViews();
    void _setRaster(int, bool setDefault = true);
    void verticalScrollSetYpos(unsigned);
	void preloadControllers();

public:

    enum
    {
	CMD_CUT_PART, CMD_COPY_PART, CMD_PASTE_PART, CMD_PASTE_CLONE_PART, CMD_PASTE_PART_TO_TRACK, CMD_PASTE_CLONE_PART_TO_TRACK,
	CMD_INSERT_PART, CMD_INSERT_EMPTYMEAS, CMD_REMOVE_SELECTED_AUTOMATION_NODES, CMD_COPY_AUTOMATION_NODES, CMD_PASTE_AUTOMATION_NODES
    };

    Composer(QMainWindow* parent, const char* name = 0);
	~Composer();

    ComposerCanvas* getCanvas()
    {
		return canvas;
    }

	void updateCanvas()
	{
		if(canvas)
			canvas->update();
	}

	CItem*  addCanvasPart(Track*);

    /*TList* getTrackList() const
    {
	    return list;
    }
	*/
	bool isEditing();
	void endEditing();

    void setMode(int);
    void reset();

    void writeStatus(int level, Xml&);
    void readStatus(Xml&);

    Track* curTrack() const
    {
	return selected;
    }
    void cmd(int);

    bool isSingleSelection()
    {
	return canvas->isSingleSelection();
    }

    int selectionSize()
    {
	return canvas->selectionSize();
    }
    void setGlobalTempo(int);
    void clear();

    unsigned cursorValue()
    {
	return cursVal;
    }


    QComboBox* raster;
};

#endif

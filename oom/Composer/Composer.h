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
class SpinBox;
class TrackViewDock;
class AudioClipList;
class CommentDock;
class CItem;
class HeaderList;
class EditToolBar;
class TimeHeader;

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
    Conductor* midiConductor;
	QScrollArea *listScroll;
	//EditToolBar *edittools;
	TimeHeader* m_timeHeader;

    Track* selected;

    LabelCombo* typeBox;
    QToolButton* ib;
    Splitter* split;
    int songType;
    PosLabel* cursorPos;
    SpinBox* globalTempoSpinBox;
    SpinBox* globalPitchSpinBox;
	QTabWidget* _rtabs;
	TrackViewDock* _tvdock;
	AudioClipList* m_clipList;
	CommentDock* _commentdock;
	QWidget *central;
	QVBoxLayout *mlayout;

    unsigned cursVal;
    void createDockMembers();
    void updateTabs();
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void songlenChanged(int);
    void trackSelectionChanged();
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
	void composerViewChanged();
	void updateAll();

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
	void trackSelectionChanged(qint64);


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
	CMD_INSERT_PART, CMD_INSERT_EMPTYMEAS, CMD_REMOVE_SELECTED_AUTOMATION_NODES, CMD_COPY_AUTOMATION_NODES, CMD_PASTE_AUTOMATION_NODES,
	CMD_SELECT_ALL_AUTOMATION
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


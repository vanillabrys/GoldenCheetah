/*
 * Copyright (c) 2009 Sean C. Rhea (srhea@srhea.net)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _GC_AllPlotWindow_h
#define _GC_AllPlotWindow_h 1
#include "GoldenCheetah.h"

#include <QtGui>
#include <QObject> // for Q_PROPERTY
#include <QFormLayout>
#include <QStyle>
#include <QStyleFactory>

class AllPlot;
class AllPlotObject;
class Context;
class QwtPlotPanner;
class QwtPlotZoomer;
class QwtPlotPicker;
class QwtPlotMarker;
class QwtArrowButton;
class RideItem;
class IntervalItem;
class IntervalSummaryWindow;
class QxtSpanSlider;
class QxtGroupBox;
class WPrime;

#include "LTMWindow.h" // for tooltip/canvaspicker

class AllPlotWindow : public GcChartWindow
{
    Q_OBJECT
    G_OBJECT

    // the plot properties are used by the layout manager
    // to save and restore the plot parameters, this is so
    // we can have multiple windows open at once with different
    // settings managed by the user.
    // in this example we might show a stacked plot and a ride
    // plot at the same time.
    Q_PROPERTY(bool stacked READ isStacked WRITE setStacked USER true)
    Q_PROPERTY(bool byseries READ isBySeries WRITE setBySeries USER true)
    Q_PROPERTY(int stackWidth READ _stackWidth WRITE setStackWidth USER true)
    Q_PROPERTY(int showGrid READ isShowGrid WRITE setShowGrid USER true)
    Q_PROPERTY(int showFull READ isShowFull WRITE setShowFull USER true)
    Q_PROPERTY(int showHelp READ isShowHelp WRITE setShowHelp USER true)
    Q_PROPERTY(int showATISS READ isShowATISS WRITE setShowATISS USER true)
    Q_PROPERTY(int showANTISS READ isShowANTISS WRITE setShowANTISS USER true)
    Q_PROPERTY(int showNP READ isShowNP WRITE setShowNP USER true)
    Q_PROPERTY(int showXP READ isShowXP WRITE setShowXP USER true)
    Q_PROPERTY(int showAP READ isShowAP WRITE setShowAP USER true)
    Q_PROPERTY(int showSpeed READ isShowSpeed WRITE setShowSpeed USER true)
    Q_PROPERTY(int showAccel READ isShowAccel WRITE setShowAccel USER true)
    Q_PROPERTY(int showCad READ isShowCad WRITE setShowCad USER true)
    Q_PROPERTY(int showTorque READ isShowTorque WRITE setShowTorque USER true)
    Q_PROPERTY(int showPower READ isShowPower WRITE setShowPower USER true)
    Q_PROPERTY(int showHr READ isShowHr WRITE setShowHr USER true)
    Q_PROPERTY(int showCadD READ isShowCadD WRITE setShowCadD USER true)
    Q_PROPERTY(int showTorqueD READ isShowTorqueD WRITE setShowTorqueD USER true)
    Q_PROPERTY(int showPowerD READ isShowPowerD WRITE setShowPowerD USER true)
    Q_PROPERTY(int showHrD READ isShowHrD WRITE setShowHrD USER true)
    Q_PROPERTY(int showAlt READ isShowAlt WRITE setShowAlt USER true)
    Q_PROPERTY(int showBalance READ isShowBalance WRITE setShowBalance USER true)
    Q_PROPERTY(int showTE READ isShowTE WRITE setShowTE USER true)
    Q_PROPERTY(int showPS READ isShowPS WRITE setShowPS USER true)
    Q_PROPERTY(int showTemp READ isShowTemp WRITE setShowTemp USER true)
    Q_PROPERTY(int showW READ isShowW WRITE setShowW USER true)
    Q_PROPERTY(int byDistance READ isByDistance WRITE setByDistance USER true)
    Q_PROPERTY(int smoothing READ smoothing WRITE setSmoothing USER true)
    Q_PROPERTY(int paintBrush READ isPaintBrush WRITE setPaintBrush USER true)

    public:

        AllPlotWindow(Context *context);
        void setData(RideItem *ride);

        bool isCompare() const { return context->isCompareIntervals; }
        bool hasReveal() { return true; }

        // highlight a selection on the plots
        void setStartSelection(AllPlot* plot, double xValue);
        void setEndSelection(AllPlot* plot, double xValue, bool newInterval, QString name);
        void clearSelection();
        void hideSelection();

        // get properties - the setters are below
        bool isStacked() const { return showStack->isChecked(); }
        bool isBySeries() const { return showBySeries->isChecked(); }
        int _stackWidth() const { return stackWidth; }
        int isShowGrid() const { return showGrid->checkState(); }
        int isShowFull() const { return showFull->checkState(); }
        int isShowHelp() const { return showHelp->checkState(); }
        int isShowATISS() const { return showATISS->checkState(); }
        int isShowANTISS() const { return showANTISS->checkState(); }
        int isShowNP() const { return showNP->checkState(); }
        int isShowXP() const { return showXP->checkState(); }
        int isShowAP() const { return showAP->checkState(); }
        int isShowAlt() const { return showAlt->checkState(); }
        int isShowSpeed() const { return showSpeed->checkState(); }
        int isShowAccel() const { return showAccel->checkState(); }
        int isShowPower() const { return showPower->currentIndex(); }
        int isShowCad() const { return showCad->checkState(); }
        int isShowTorque() const { return showTorque->checkState(); }
        int isShowHr() const { return showHr->checkState(); }
        int isShowPowerD() const { return showPowerD->checkState(); }
        int isShowCadD() const { return showCadD->checkState(); }
        int isShowTorqueD() const { return showTorqueD->checkState(); }
        int isShowHrD() const { return showHrD->checkState(); }
        int isShowTE() const { return showTE->checkState(); }
        int isShowPS() const { return showPS->checkState(); }
        int isShowBalance() const { return showBalance->checkState(); }
        int isShowTemp() const { return showTemp->checkState(); }
        int isShowW() const { return showW->checkState(); }
        int isByDistance() const { return comboDistance->currentIndex(); }
        int isPaintBrush() const { return paintBrush->isChecked(); }
        int smoothing() const { return smoothSlider->value(); }

   public slots:

        // trap GC signals
        void rideSelected();
        void rideDeleted(RideItem *ride);
        void intervalSelected();
        void zonesChanged();
        void intervalsChanged();
        void configChanged();

        // set properties
        void setSmoothingFromSlider();
        void setSmoothingFromLineEdit();
        void setrSmoothingFromSlider();
        void setrSmoothingFromLineEdit();
        void setStackWidth(int x);
        void setShowNP(int state);
        void setShowATISS(int state);
        void setShowANTISS(int state);
        void setShowXP(int state);
        void setShowAP(int state);
        void setShowSpeed(int state);
        void setShowAccel(int state);
        void setShowAlt(int state);
        void setShowTemp(int state);
        void setShowWind(int state);
        void setShowPower(int state);
        void setShowCad(int state);
        void setShowTorque(int state);
        void setShowHr(int state);
        void setShowPowerD(int state);
        void setShowCadD(int state);
        void setShowTorqueD(int state);
        void setShowHrD(int state);
        void setShowBalance(int state);
        void setShowPS(int state);
        void setShowTE(int state);
        void setShowW(int state);
        void setShowGrid(int state);
        void setPaintBrush(int state);
        void setShowFull(int state);
        void setShowHelp(int state);
        void setSmoothing(int value);
        void setByDistance(int value);
        void setStacked(int value);
        void setBySeries(int value);

        // trap widget signals
        void zoomChanged();
        void zoomOut();
        void zoomInterval(IntervalItem *);
        void stackZoomSliderChanged();
        void resizeSeriesPlots();
        void resizeComparePlots();
        void moveLeft();
        void moveRight();
        void showStackChanged(int state);
        void showBySeriesChanged(int state);

        // compare mode started or items to compare changed
        void compareChanged();

    protected:

        // whilst we refactor, lets make friend
        friend class IntervalPlotData;
        friend class Context;
        friend class AllPlot;

        void setAllPlotWidgets(RideItem *rideItem);
        bool event(QEvent *event);

        // cached state
        RideItem *current;
        int selection;
        Context *context;

        // All the plot widgets
        QVBoxLayout *allPlotLayout;
        AllPlot *allPlot;
        AllPlot *fullPlot;
        QList <AllPlot *> allPlots;
        QList <AllPlot *> seriesPlots;
        QwtPlotPanner *allPanner;
        QwtPlotZoomer *allZoomer;

        QStackedWidget *allStack; // for normal allplot of stacked al plot in compare mode

        // compare mode all plot (is a stack view, not a single plot)
        QScrollArea *comparePlotFrame;
        QVBoxLayout *comparePlotLayout;
        QWidget *comparePlotWidget;
        QList<AllPlot*> allComparePlots; // allplot as a series of charts

        // Stacked view
        QScrollArea *stackFrame;
        QVBoxLayout *stackPlotLayout;
        QWidget *stackWidget;

        // series stack view
        QScrollArea *seriesstackFrame;
        QVBoxLayout *seriesstackPlotLayout;
        QWidget *seriesstackWidget;

        // stack zoomer for setting stack width
        // has 8 settings from 0 - 7
        QSlider *stackZoomSlider;

        // Normal view
        QScrollArea *allPlotFrame;
        QPushButton *scrollLeft, *scrollRight;

        // Common controls
        QGridLayout *controlsLayout;
        QCheckBox *showStack;
        QCheckBox *showBySeries;
        QCheckBox *showGrid;
        QCheckBox *showFull;
        QCheckBox *showHelp;
        QCheckBox *paintBrush;
        QCheckBox *showAlt;
        QCheckBox *showATISS;
        QCheckBox *showANTISS;
        QCheckBox *showNP;
        QCheckBox *showXP;
        QCheckBox *showAP;
        QCheckBox *showSpeed;
        QCheckBox *showAccel;
        QComboBox *showPower;
        QCheckBox *showCad;
        QCheckBox *showTorque;
        QCheckBox *showHr;
        QCheckBox *showPowerD;
        QCheckBox *showCadD;
        QCheckBox *showTorqueD;
        QCheckBox *showHrD;
        QCheckBox *showTemp;
        QCheckBox *showWind;
        QCheckBox *showBalance;
        QCheckBox *showTE;
        QCheckBox *showPS;
        QCheckBox *showW;
        QComboBox *comboDistance;
        QSlider *smoothSlider;
        QLineEdit *smoothLineEdit;
        QxtSpanSlider *spanSlider;

    private:
        // reveal controls
        QLabel *rSmooth;
        QSlider *rSmoothSlider;
        QLineEdit *rSmoothEdit;
        QCheckBox *rStack, *rBySeries, *rFull, *rHelp;
        QStackedWidget *allPlotStack;
        IntervalSummaryWindow *overlayIntervals;

        // comparing 
        QList<AllPlotObject*> compareIntervalCurves; // one per compareInterval

        // reset/redraw all the plots
        void setupStackPlots();
        void forceSetupSeriesStackPlots();
        void setupSeriesStackPlots();
        void redrawAllPlot();
        void redrawFullPlot();
        void redrawStackPlot();

        void showInfo(QString);
        void resetStackedDatas();
        void resetSeriesStackedDatas();
        int stackWidth;

        bool active;
        bool stale;
        bool setupStack;       // we optimise this out, its costly
        bool setupSeriesStack; // we optimise this out, its costly
        bool compareStale;     // compare init one off setup
        bool firstShow;

    private slots:

        void addPickers(AllPlot *allPlot2);
        void plotPickerMoved(const QPoint &);
        void plotPickerSelected(const QPoint &);
};

#endif // _GC_AllPlotWindow_h

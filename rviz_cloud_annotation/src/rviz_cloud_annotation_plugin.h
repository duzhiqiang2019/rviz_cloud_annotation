/*
 * Copyright (c) 2016, Riccardo Monica
 */

#ifndef RVIZ_CLOUD_ANNOTATION_PLUGIN_H
#define RVIZ_CLOUD_ANNOTATION_PLUGIN_H

#include <ros/ros.h>
#include <rviz/panel.h>
#include <std_msgs/UInt32.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt64MultiArray.h>

#include <stdint.h>
#include <vector>

class QLabel;
class QPushButton;
class QButtonGroup;
class QLineEdit;
class QAction;
class QToolButton;

namespace rviz_cloud_annotation
{

  class QRVizCloudAnnotation: public rviz::Panel
  {
    Q_OBJECT;

    typedef uint64_t uint64;
    typedef std::vector<uint64> Uint64Vector;
    typedef std::vector<QPushButton *> PQPushButtonVector;

    public:
    QRVizCloudAnnotation(QWidget* parent = NULL);
    virtual ~QRVizCloudAnnotation();

    private Q_SLOTS:
    void onSetEditMode(int mode);

    void onLabelButtonSelected(int id);
    void onPlusLabel();
    void onMinusLabel();
    void onPageUp();
    void onPageDown();

    void onSave();
    void onRestore();
    void onClear();
    void onClearCurrent();

    void onSendName();

    void onViewCloudToggled(const bool checked);
    void onViewControlPointsToggled(const bool checked);
    void onViewLabelsToggled(const bool checked);

    private:
    void SetCurrentEditMode(const uint64 mode);

    void FillColorPageButtons();
    void FillPointCounts();

    void SetCurrentLabel(const uint64 label,const uint64 page);

    void onSetCurrentLabel(const std_msgs::UInt32 & label);
    void onSetEditMode2(const std_msgs::UInt32 & mode);
    void onPointCountUpdate(const std_msgs::UInt64MultiArray & counters);

    void onSetName(const std_msgs::String & name);

    uint64 GetPageForLabel(const uint64 label) const;
    uint64 GetLabelFromPageAndId(const uint64 page,const int id) const;
    uint64 GetFirstLabelForPage(const uint64 page) const;
    uint64 GetLastLabelForPage(const uint64 page) const;

    uint64 m_current_edit_mode;

    // 0 for the eraser
    uint64 m_current_label;
    uint64 m_current_page;

    ros::NodeHandle m_nh;
    ros::Publisher m_set_edit_mode_pub;
    ros::Publisher m_set_current_label_pub;

    ros::Publisher m_save_pub;
    ros::Publisher m_restore_pub;
    ros::Publisher m_clear_pub;

    ros::Subscriber m_set_edit_mode_sub;
    ros::Subscriber m_set_current_label_sub;

    ros::Publisher m_set_name_pub;
    ros::Subscriber m_set_name_sub;

    ros::Publisher m_view_cloud_pub;
    ros::Publisher m_view_labels_pub;
    ros::Publisher m_view_control_points_pub;

    QPushButton * m_edit_none_button;
    QPushButton * m_edit_control_point_button;
    QPushButton * m_edit_eraser_button;
    QPushButton * m_edit_color_picker_button;
    QButtonGroup * m_toolbar_group;

    QAction * m_prev_page_action;
    QAction * m_next_page_action;
    QAction * m_next_label_action;
    QAction * m_prev_label_action;

    QLabel * m_current_page_label;

    PQPushButtonVector m_page_buttons;
    QButtonGroup * m_page_button_group;

    Uint64Vector m_point_counters;
    ros::Subscriber m_point_count_update_sub;

    QLineEdit * m_set_name_edit;

    uint64 m_color_cols_per_page;
    uint64 m_color_rows_per_page;
  };

}

#endif // RVIZ_CLOUD_ANNOTATION_PLUGIN_H
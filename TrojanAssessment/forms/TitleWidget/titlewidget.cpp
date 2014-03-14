#include "titlewidget.h"

TitleWidget::TitleWidget(QWidget *parent)
	: QWidget(parent)
{
	m_mainLayout = new QVBoxLayout(this);
	//////////////////////////////////////////////////////////////////////////
	// initialize top part
	m_topLayout = new QHBoxLayout(this);
	m_windowTitle = new QLabel(QStringLiteral("Trojan Assessment Platform"), this);
	m_settings = new CustomPushButton(this);
	m_minBtn = new CustomPushButton(this);
	m_closeBtn = new CustomPushButton(this);
	m_settings->setBtnBackground(QStringLiteral(":/SysButtons/menu"));
	m_minBtn->setBtnBackground(QStringLiteral(":/SysButtons/min"));
	m_closeBtn->setBtnBackground(QStringLiteral(":/SysButtons/close"));

	m_topLayout->addWidget(m_windowTitle, 0, Qt::AlignCenter);
	m_topLayout->addStretch();
	m_topLayout->addWidget(m_settings, 0, Qt::AlignTop);
	m_topLayout->addWidget(m_minBtn, 0, Qt::AlignTop);
	m_topLayout->addWidget(m_closeBtn, 0, Qt::AlignTop);
	m_topLayout->setSpacing(0);
	m_topLayout->setContentsMargins(10, 0, 10, 0);
	//////////////////////////////////////////////////////////////////////////
	// initialize bottom part
	m_bottomLayout = new QHBoxLayout(this);
	QStringList strList;
	strList << ":/ToolButtons/fileTab" << ":/ToolButtons/IETab" << ":/ToolButtons/memoryTab"
		    << ":/ToolButtons/networkTab" << ":/ToolButtons/processTab" << ":/ToolButtons/registryTab"
			<< ":/ToolButtons/assessmentTab";
	QSignalMapper* sigMapper = new QSignalMapper(this);
	for (int i = 0; i < strList.size(); ++i)
	{
		// create a custom tool button
		CustomToolButton* tmpBtn = new CustomToolButton(strList.at(i));
		connect(tmpBtn, SIGNAL(clicked()), sigMapper, SLOT(map()));
		m_toolBtnList.append(tmpBtn);
		// establish a mapping between the string and widget pointer.
		sigMapper->setMapping(tmpBtn, QString::number(i, 10));
		m_bottomLayout->addWidget(tmpBtn, 0, Qt::AlignBottom);
	}
	connect(sigMapper, SIGNAL(mapped(const QString&)), this, SLOT(onToolBtnClicked(const QString&)));
	m_bottomLayout->addStretch();
	m_bottomLayout->setSpacing(10);
	m_bottomLayout->setContentsMargins(15, 0, 15, 0);

	//////////////////////////////////////////////////////////////////////////
	m_mainLayout->addLayout(m_topLayout);
	m_mainLayout->addLayout(m_bottomLayout);
	m_mainLayout->setSpacing(0);
	m_mainLayout->setContentsMargins(0, 0, 0, 0);
	// apply the layout
	setLayout(m_mainLayout);
	// make the height of main window constant
	setFixedHeight(110);
	// connect slots with signals
	connect(m_settings, SIGNAL(clicked()), this, SIGNAL(SettingsBtnClicked()));
	connect(m_minBtn, SIGNAL(clicked()), this, SIGNAL(ShowMinimizedBtnClicked()));
	connect(m_closeBtn, SIGNAL(clicked()), this, SIGNAL(CloseWindowBtnClicked()));
}

TitleWidget::~TitleWidget()
{

}

/*
 * Update the tool buttons' states and signal the parent widget
 * to change corresponding page.
 */
void TitleWidget::onToolBtnClicked(const QString& obj)
{
	int index = obj.toInt();

	for (int i = 0; i < m_toolBtnList.size(); ++i)
	{
		CustomToolButton* tmpBtn = m_toolBtnList.at(i);
		// normalize all tool buttons except the one the user clicked.
		tmpBtn->setButtonPressed(i==index?true:false);
	}
	emit ToolBtnClicked(index);
}
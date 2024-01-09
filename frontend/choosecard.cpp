/*#include "choosecard.h"
#include "ui_choosecard.h"
#include "selectactionmenu.h"


chooseCard::chooseCard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseCard)
{
    ui->setupUi(this);

    // heti ensimmäisenä tänne tullessa vertaillaan kortteja ja niiden tilejä
    // jos on vain 1 tili, siirrytään suoraan avaaTili()-kohtaan
    // jos on 2 tiliä tai enemmän, siirrytään kortin valintaan

    //kesken:
    connect(ui->nappi_credit, SIGNAL(clicked(bool)), this, SLOT(avaaTili()));
    connect(ui->nappi_debit, SIGNAL(clicked(bool)), this, SLOT(avaaTili()));
}

chooseCard::~chooseCard()
{
    +
    delete ui;
}

void chooseCard::avaaTili()
{
    // avataan korttinron osoittama tilivalikko
    selectActionMenu *selectActionMenuOlio = new selectActionMenu(this);
    selectActionMenuOlio->setKortti_nro(kortti_nro);
    selectActionMenuOlio->setToken(token);
    selectActionMenuOlio->open();
}*/

#include "mainwindowex3.h"
#include "ui_mainwindowex3.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

MainWindowEx3::MainWindowEx3(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindowEx3)
{
    ui->setupUi(this);

    // ==========================================
    // ÉTAPE 5 : REDIRECTION DE STDERR
    // ==========================================
    int fd = open("Trace.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd != -1)
    {
        dup2(fd, 2);
        
        ::close(fd);
    }
}

MainWindowEx3::~MainWindowEx3()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx3::setGroupe1(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe1->clear();
    return;
  }
  ui->lineEditGroupe1->setText(Text);
}

void MainWindowEx3::setGroupe2(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe2->clear();
    return;
  }
  ui->lineEditGroupe2->setText(Text);
}

void MainWindowEx3::setGroupe3(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe3->clear();
    return;
  }
  ui->lineEditGroupe3->setText(Text);
}

void MainWindowEx3::setResultat1(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat1->clear();
    return;
  }
  ui->lineEditResultat1->setText(Text);
}

void MainWindowEx3::setResultat2(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat2->clear();
    return;
  }
  ui->lineEditResultat2->setText(Text);
}

void MainWindowEx3::setResultat3(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat3->clear();
    return;
  }
  ui->lineEditResultat3->setText(Text);
}

bool MainWindowEx3::recherche1Selectionnee()
{
  return ui->checkBoxRecherche1->isChecked();
}

bool MainWindowEx3::recherche2Selectionnee()
{
  return ui->checkBoxRecherche2->isChecked();
}

bool MainWindowEx3::recherche3Selectionnee()
{
  return ui->checkBoxRecherche3->isChecked();
}

const char* MainWindowEx3::getGroupe1()
{
  if (ui->lineEditGroupe1->text().size())
  { 
    strcpy(groupe1,ui->lineEditGroupe1->text().toStdString().c_str());
    return groupe1;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe2()
{
  if (ui->lineEditGroupe2->text().size())
  { 
    strcpy(groupe2,ui->lineEditGroupe2->text().toStdString().c_str());
    return groupe2;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe3()
{
  if (ui->lineEditGroupe3->text().size())
  { 
    strcpy(groupe3,ui->lineEditGroupe3->text().toStdString().c_str());
    return groupe3;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx3::on_pushButtonLancerRecherche_clicked()
{
  fprintf(stderr,"Clic sur le bouton Lancer Recherche\n");
  
  pid_t idFils1 = 0, idFils2 = 0, idFils3 = 0;
  int nbFilsLances = 0;

  // --- RECHERCHE 1 ---
  if (recherche1Selectionnee())
  {
    const char* groupe = getGroupe1();
    if (groupe != NULL)
    {
      idFils1 = fork();
      if (idFils1 == 0)
      {
        execl("./Lecture", "Lecture", groupe, NULL);
        perror("Erreur execl 1");
        exit(1);
      }
      else if (idFils1 > 0)
      {
        nbFilsLances++;
      }
    }
  }

  // --- RECHERCHE 2 ---
  if (recherche2Selectionnee())
  {
    const char* groupe = getGroupe2();
    if (groupe != NULL)
    {
      idFils2 = fork();
      if (idFils2 == 0)
      {
        execl("./Lecture", "Lecture", groupe, NULL);
        perror("Erreur execl 2");
        exit(1);
      }
      else if (idFils2 > 0)
      {
        nbFilsLances++;
      }
    }
  }

  // --- RECHERCHE 3 ---
  if (recherche3Selectionnee())
  {
    const char* groupe = getGroupe3();
    if (groupe != NULL)
    {
      idFils3 = fork();
      if (idFils3 == 0)
      {
        execl("./Lecture", "Lecture", groupe, NULL);
        perror("Erreur execl 3");
        exit(1);
      }
      else if (idFils3 > 0)
      {
        nbFilsLances++;
      }
    }
  }

  // --- ATTENTE DES FILS ET AFFICHAGE ---
  int status;
  pid_t idTermine;

  for (int i = 0; i < nbFilsLances; i++)
  {
    idTermine = wait(&status);

    if (WIFEXITED(status))
    {
      int nbEtudiants = WEXITSTATUS(status);

      if (idTermine == idFils1) 
      {
        setResultat1(nbEtudiants);
      }
      else if (idTermine == idFils2) 
      {
        setResultat2(nbEtudiants);
      }
      else if (idTermine == idFils3) 
      {
        setResultat3(nbEtudiants);
      }
    }
  }
}

void MainWindowEx3::on_pushButtonVider_clicked()
{
  fprintf(stderr,"Clic sur le bouton Vider\n");
  setGroupe1("");
  setGroupe2("");
  setGroupe3("");
  ui->lineEditResultat1->clear();
  ui->lineEditResultat2->clear();
  ui->lineEditResultat3->clear();
}

void MainWindowEx3::on_pushButtonQuitter_clicked()
{
  fprintf(stderr,"Clic sur le bouton Quitter\n");
  exit(0);
}
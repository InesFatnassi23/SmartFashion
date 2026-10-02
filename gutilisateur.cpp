#include "gutilisateur.h"

#include <algorithm>

#include <QAbstractItemView>
#include <QComboBox>
#include <QDateTime>
#include <QDialog>
#include <QFileDialog>
#include <QFont>
#include <QHeaderView>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPageLayout>
#include <QPageSize>
#include <QPainter>
#include <QPaintEvent>
#include <QPdfWriter>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMap>
#include <QList>
#include <QStringList>
#include <QRectF>
#include <QtGlobal>

namespace {

const QString MENU_NORMAL =
    "QPushButton {"
    " background-color: transparent;"
    " color: white;"
    " border: none;"
    " border-radius: 9px;"
    " padding: 12px;"
    " text-align: left;"
    " padding-left: 18px;"
    " font-size: 15px;"
    "}"
    "QPushButton:hover {"
    " background-color: #6B1A27;"
    "}";

const QString MENU_ACTIVE =
    "QPushButton {"
    " background-color: #C19345;"
    " color: white;"
    " border: none;"
    " border-radius: 9px;"
    " padding: 12px;"
    " text-align: left;"
    " padding-left: 18px;"
    " font-size: 15px;"
    " font-weight: bold;"
    "}"
    "QPushButton:hover {"
    " background-color: #D0A354;"
    "}";

const QString INPUT_STYLE =
    "QLineEdit, QComboBox {"
    " background-color: #FFFDF9;"
    " border: 1px solid #D6CEC3;"
    " border-radius: 6px;"
    " padding: 7px;"
    " font-size: 14px;"
    " color: #4A2028;"
    "}"
    "QLineEdit:focus, QComboBox:focus {"
    " border: 2px solid #C19345;"
    "}";

const QString ACTION_STYLE =
    "QPushButton {"
    " background-color: #651522;"
    " color: white;"
    " border: none;"
    " border-radius: 6px;"
    " padding: 9px;"
    " font-size: 14px;"
    "}"
    "QPushButton:hover {"
    " background-color: #7B1C2A;"
    "}"
    "QPushButton:pressed {"
    " background-color: #500F1A;"
    "}";

const QString QUIT_STYLE =
    "QPushButton {"
    " background-color: #FFFDF9;"
    " color: #651522;"
    " border: 1px solid #C19345;"
    " border-radius: 6px;"
    " padding: 9px;"
    " font-size: 14px;"
    "}"
    "QPushButton:hover {"
    " background-color: #F3E8D7;"
    "}";

QPushButton *creerBoutonMenu(const QString &texte, QWidget *parent)
{
    auto *bouton = new QPushButton(texte, parent);
    bouton->setFixedHeight(45);
    bouton->setStyleSheet(MENU_NORMAL);
    return bouton;
}

QPushButton *creerBoutonAction(const QString &texte, QWidget *parent)
{
    auto *bouton = new QPushButton(texte, parent);
    bouton->setFixedHeight(45);
    bouton->setStyleSheet(ACTION_STYLE);
    return bouton;
}

}

gutilisateur::gutilisateur(QWidget *parent)
    : QMainWindow(parent),
    idEdit(new QLineEdit(this)),
    nomEdit(new QLineEdit(this)),
    prenomEdit(new QLineEdit(this)),
    passwordEdit(new QLineEdit(this)),
    roleCombo(new QComboBox(this)),
    table(new QTableWidget(this)),
    ajouterBtn(nullptr),
    modifierBtn(nullptr),
    supprimerBtn(nullptr),
    afficherBtn(nullptr),
    quitterBtn(nullptr),
    trierBtn(nullptr),
    rechercherBtn(nullptr),
    pdfBtn(nullptr),
    statistiquesBtn(nullptr),
    dashboardBtn(nullptr),
    usersMenu(nullptr),
    clientsBtn(nullptr),
    collectionsBtn(nullptr),
    fournisseursBtn(nullptr),
    equipementsBtn(nullptr),
    pageTitle(new QLabel(this))
{
    setWindowTitle("ChéChic | Gestion des utilisateurs");
    resize(1200, 720);
    setMinimumSize(1000, 650);

    auto *central = new QWidget(this);
    setCentralWidget(central);

    auto *rootLayout = new QVBoxLayout(central);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    auto *header = new QWidget(central);
    header->setFixedHeight(80);
    header->setStyleSheet("background-color: #651522;");

    auto *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(15, 0, 25, 0);

    auto *logo = new QLabel("ChéChic", header);
    logo->setStyleSheet(
        "color: #D1A052;"
        "font-size: 27px;"
        "font-family: Georgia;"
        "font-style: italic;"
        "font-weight: bold;"
        );

    pageTitle->setText("Gestion des utilisateurs");
    pageTitle->setStyleSheet(
        "color: white;"
        "font-size: 23px;"
        "font-weight: bold;"
        );

    headerLayout->addWidget(logo);
    headerLayout->addStretch();
    headerLayout->addWidget(pageTitle);
    headerLayout->addStretch();
    rootLayout->addWidget(header);

    auto *content = new QWidget(central);
    content->setStyleSheet("background-color: #F8F4EE;");

    auto *contentLayout = new QHBoxLayout(content);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setSpacing(0);

    auto *sidebar = new QWidget(content);
    sidebar->setFixedWidth(183);
    sidebar->setStyleSheet("background-color: #500F1A;");

    auto *sideLayout = new QVBoxLayout(sidebar);
    sideLayout->setContentsMargins(12, 30, 12, 20);
    sideLayout->setSpacing(10);

    dashboardBtn = creerBoutonMenu("Tableau de bord", sidebar);
    usersMenu = creerBoutonMenu("Utilisateurs", sidebar);
    clientsBtn = creerBoutonMenu("Clients", sidebar);
    collectionsBtn = creerBoutonMenu("Collections", sidebar);
    fournisseursBtn = creerBoutonMenu("Fournisseurs", sidebar);
    equipementsBtn = creerBoutonMenu("Équipements", sidebar);

    sideLayout->addWidget(dashboardBtn);
    sideLayout->addWidget(usersMenu);
    sideLayout->addWidget(clientsBtn);
    sideLayout->addWidget(collectionsBtn);
    sideLayout->addWidget(fournisseursBtn);
    sideLayout->addWidget(equipementsBtn);
    sideLayout->addStretch();

    contentLayout->addWidget(sidebar);

    auto *mainWidget = new QWidget(content);
    auto *centerLayout = new QHBoxLayout(mainWidget);
    centerLayout->setContentsMargins(20, 20, 20, 20);
    centerLayout->setSpacing(25);

    auto *formBox = new QWidget(mainWidget);
    formBox->setFixedWidth(330);
    formBox->setStyleSheet(
        "QWidget {"
        " background-color: #FFFDF9;"
        " border: 1px solid #DDD5CB;"
        " border-radius: 10px;"
        "}"
        "QLabel {"
        " color: #551A25;"
        " border: none;"
        "}"
        );

    auto *formLayout = new QVBoxLayout(formBox);
    formLayout->setContentsMargins(20, 20, 20, 20);
    formLayout->setSpacing(2);

    auto *formTitle = new QLabel("Informations utilisateur", formBox);
    formTitle->setStyleSheet(
        "color: #551A25;"
        "font-size: 19px;"
        "font-weight: bold;"
        "border: none;"
        );
    formLayout->addWidget(formTitle);

    idEdit->setPlaceholderText("ID");
    nomEdit->setPlaceholderText("Nom");
    prenomEdit->setPlaceholderText("Prénom");
    passwordEdit->setPlaceholderText("Mot de passe");
    passwordEdit->setEchoMode(QLineEdit::Password);

    roleCombo->addItems({
        "Administrateur",
        "Manager",
        "Employé"
    });

    idEdit->setStyleSheet(INPUT_STYLE);
    nomEdit->setStyleSheet(INPUT_STYLE);
    prenomEdit->setStyleSheet(INPUT_STYLE);
    passwordEdit->setStyleSheet(INPUT_STYLE);
    roleCombo->setStyleSheet(INPUT_STYLE);

    formLayout->addWidget(new QLabel("ID", formBox));
    formLayout->addWidget(idEdit);
    formLayout->addWidget(new QLabel("Nom", formBox));
    formLayout->addWidget(nomEdit);
    formLayout->addWidget(new QLabel("Prénom", formBox));
    formLayout->addWidget(prenomEdit);
    formLayout->addWidget(new QLabel("Mot de passe", formBox));
    formLayout->addWidget(passwordEdit);
    formLayout->addWidget(new QLabel("Rôle", formBox));
    formLayout->addWidget(roleCombo);
    formLayout->addStretch();

    ajouterBtn = creerBoutonAction("➕ Ajouter", formBox);
    modifierBtn = creerBoutonAction("✏️ Modifier", formBox);
    supprimerBtn = creerBoutonAction("🗑️ Supprimer", formBox);
    afficherBtn = creerBoutonAction("👁️ Afficher", formBox);

    quitterBtn = new QPushButton("🚪 Quitter", formBox);
    quitterBtn->setFixedHeight(45);
    quitterBtn->setStyleSheet(QUIT_STYLE);

    // Espacement demandé uniquement entre les boutons.
    formLayout->addWidget(ajouterBtn);
    formLayout->addSpacing(15);
    formLayout->addWidget(modifierBtn);
    formLayout->addSpacing(15);
    formLayout->addWidget(supprimerBtn);
    formLayout->addSpacing(15);
    formLayout->addWidget(afficherBtn);
    formLayout->addSpacing(15);
    formLayout->addWidget(quitterBtn);

    centerLayout->addWidget(formBox);

    auto *tableBox = new QWidget(mainWidget);
    auto *tableLayout = new QVBoxLayout(tableBox);
    tableLayout->setContentsMargins(0, 0, 0, 0);
    tableLayout->setSpacing(12);

    auto *tableTitle = new QLabel("Liste des utilisateurs", tableBox);
    tableTitle->setStyleSheet(
        "color: #551A25;"
        "font-size: 20px;"
        "font-weight: bold;"
        );
    tableLayout->addWidget(tableTitle);

    auto *featuresLayout = new QHBoxLayout();
    featuresLayout->setSpacing(8);

    trierBtn = creerBoutonAction("↕ Trier", tableBox);
    rechercherBtn = creerBoutonAction("🔎 Rechercher ID", tableBox);
    pdfBtn = creerBoutonAction("📄 Exporter PDF", tableBox);
    statistiquesBtn = creerBoutonAction("📊 Statistiques", tableBox);

    trierBtn->setToolTip("Trier par Nom puis Prénom");
    rechercherBtn->setToolTip("Rechercher un utilisateur par ID");
    pdfBtn->setToolTip("Exporter les utilisateurs en PDF");
    statistiquesBtn->setToolTip("Afficher les statistiques du temps de travail");

    featuresLayout->addWidget(trierBtn);
    featuresLayout->addWidget(rechercherBtn);
    featuresLayout->addWidget(pdfBtn);
    featuresLayout->addWidget(statistiquesBtn);
    tableLayout->addLayout(featuresLayout);

    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({
        "ID", "Nom", "Prénom", "Mot de passe", "Rôle"
    });
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSortingEnabled(false);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);

    table->setStyleSheet(
        "QTableWidget {"
        " background-color: #FFFDF9;"
        " border: 1px solid #D8CEC2;"
        " border-radius: 7px;"
        " gridline-color: #E5DDD3;"
        " color: #4B2029;"
        " font-size: 13px;"
        "}"
        "QTableWidget::item { padding: 7px; }"
        "QTableWidget::item:selected {"
        " background-color: #C19345;"
        " color: white;"
        "}"
        "QHeaderView::section {"
        " background-color: #651522;"
        " color: white;"
        " padding: 9px;"
        " font-weight: bold;"
        " border: none;"
        "}"
        );

    tableLayout->addWidget(table, 1);
    centerLayout->addWidget(tableBox, 1);
    contentLayout->addWidget(mainWidget, 1);
    rootLayout->addWidget(content, 1);

    connect(ajouterBtn, &QPushButton::clicked,
            this, &gutilisateur::ajouterUtilisateur);
    connect(modifierBtn, &QPushButton::clicked,
            this, &gutilisateur::modifierUtilisateur);
    connect(supprimerBtn, &QPushButton::clicked,
            this, &gutilisateur::supprimerUtilisateur);
    connect(afficherBtn, &QPushButton::clicked,
            this, &gutilisateur::afficherUtilisateur);
    connect(quitterBtn, &QPushButton::clicked,
            this, &gutilisateur::quitter);
    connect(table, &QTableWidget::cellClicked,
            this, &gutilisateur::selectionnerUtilisateur);
    connect(trierBtn, &QPushButton::clicked,
            this, &gutilisateur::trierUtilisateurs);
    connect(rechercherBtn, &QPushButton::clicked,
            this, &gutilisateur::rechercherParId);
    connect(pdfBtn, &QPushButton::clicked,
            this, &gutilisateur::exporterPDF);
    connect(statistiquesBtn, &QPushButton::clicked,
            this, &gutilisateur::afficherStatistiques);

    connect(dashboardBtn, &QPushButton::clicked,
            this, &gutilisateur::ouvrirTableauDeBord);
    connect(usersMenu, &QPushButton::clicked,
            this, &gutilisateur::ouvrirUtilisateurs);
    connect(clientsBtn, &QPushButton::clicked,
            this, &gutilisateur::ouvrirClients);
    connect(collectionsBtn, &QPushButton::clicked,
            this, &gutilisateur::ouvrirCollections);
    connect(fournisseursBtn, &QPushButton::clicked,
            this, &gutilisateur::ouvrirFournisseurs);
    connect(equipementsBtn, &QPushButton::clicked,
            this, &gutilisateur::ouvrirEquipements);

    activerMenu(usersMenu);
}

void gutilisateur::activerMenu(QPushButton *boutonActif)
{
    const QList<QPushButton*> boutons = {
        dashboardBtn, usersMenu, clientsBtn,
        collectionsBtn, fournisseursBtn, equipementsBtn
    };

    for (QPushButton *bouton : boutons) {
        if (!bouton)
            continue;
        bouton->setStyleSheet(
            bouton == boutonActif ? MENU_ACTIVE : MENU_NORMAL
            );
    }
}

bool gutilisateur::idExiste(const QString &id, int ligneIgnoree) const
{
    for (int ligne = 0; ligne < table->rowCount(); ++ligne) {
        if (ligne == ligneIgnoree)
            continue;

        QTableWidgetItem *item = table->item(ligne, 0);
        if (item && item->text().trimmed() == id.trimmed())
            return true;
    }
    return false;
}

QString gutilisateur::valeurCellule(int ligne, int colonne) const
{
    if (ligne < 0 || ligne >= table->rowCount())
        return QString();

    QTableWidgetItem *item = table->item(ligne, colonne);
    return item ? item->text() : QString();
}

void gutilisateur::viderFormulaire()
{
    idEdit->clear();
    nomEdit->clear();
    prenomEdit->clear();
    passwordEdit->clear();
    roleCombo->setCurrentIndex(0);
    table->clearSelection();
}

void gutilisateur::selectionnerUtilisateur()
{
    const int ligne = table->currentRow();
    if (ligne < 0)
        return;

    idEdit->setText(valeurCellule(ligne, 0));
    nomEdit->setText(valeurCellule(ligne, 1));
    prenomEdit->setText(valeurCellule(ligne, 2));
    passwordEdit->setText(valeurCellule(ligne, 3));

    const int index = roleCombo->findText(valeurCellule(ligne, 4));
    if (index >= 0)
        roleCombo->setCurrentIndex(index);
}

void gutilisateur::ajouterUtilisateur()
{
    const QString id = idEdit->text().trimmed();
    const QString nom = nomEdit->text().trimmed();
    const QString prenom = prenomEdit->text().trimmed();
    const QString password = passwordEdit->text();

    if (id.isEmpty() || nom.isEmpty() || prenom.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(
            this, "Champs manquants",
            "Veuillez remplir tous les champs obligatoires."
            );
        return;
    }

    if (idExiste(id)) {
        QMessageBox::warning(
            this, "ID existant",
            "Cet ID utilisateur existe déjà."
            );
        return;
    }

    const int ligne = table->rowCount();
    table->insertRow(ligne);
    table->setItem(ligne, 0, new QTableWidgetItem(id));
    table->setItem(ligne, 1, new QTableWidgetItem(nom));
    table->setItem(ligne, 2, new QTableWidgetItem(prenom));
    table->setItem(ligne, 3, new QTableWidgetItem(password));
    table->setItem(ligne, 4, new QTableWidgetItem(roleCombo->currentText()));

    tempsTravail[id] = 0.0;
    viderFormulaire();

    QMessageBox::information(
        this, "Ajout",
        "Utilisateur ajouté avec succès."
        );
}

void gutilisateur::modifierUtilisateur()
{
    const int ligne = table->currentRow();
    if (ligne < 0) {
        QMessageBox::warning(
            this, "Modification",
            "Veuillez sélectionner un utilisateur."
            );
        return;
    }

    const QString ancienId = valeurCellule(ligne, 0);
    const QString id = idEdit->text().trimmed();
    const QString nom = nomEdit->text().trimmed();
    const QString prenom = prenomEdit->text().trimmed();
    const QString password = passwordEdit->text();

    if (id.isEmpty() || nom.isEmpty() || prenom.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(
            this, "Champs manquants",
            "Veuillez remplir tous les champs obligatoires."
            );
        return;
    }

    if (idExiste(id, ligne)) {
        QMessageBox::warning(
            this, "ID existant",
            "Cet ID utilisateur existe déjà."
            );
        return;
    }

    table->item(ligne, 0)->setText(id);
    table->item(ligne, 1)->setText(nom);
    table->item(ligne, 2)->setText(prenom);
    table->item(ligne, 3)->setText(password);
    table->item(ligne, 4)->setText(roleCombo->currentText());

    if (ancienId != id && tempsTravail.contains(ancienId)) {
        tempsTravail[id] = tempsTravail.value(ancienId);
        tempsTravail.remove(ancienId);
    }

    viderFormulaire();

    QMessageBox::information(
        this, "Modification",
        "Utilisateur modifié avec succès."
        );
}

void gutilisateur::supprimerUtilisateur()
{
    const int ligne = table->currentRow();
    if (ligne < 0) {
        QMessageBox::warning(
            this, "Suppression",
            "Veuillez sélectionner un utilisateur."
            );
        return;
    }

    const auto reponse = QMessageBox::question(
        this,
        "Confirmation",
        "Voulez-vous supprimer cet utilisateur ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reponse != QMessageBox::Yes)
        return;

    const QString id = valeurCellule(ligne, 0);
    table->removeRow(ligne);
    tempsTravail.remove(id);
    viderFormulaire();

    QMessageBox::information(
        this, "Suppression",
        "Utilisateur supprimé avec succès."
        );
}

void gutilisateur::afficherUtilisateur()
{
    const int ligne = table->currentRow();
    if (ligne < 0) {
        QMessageBox::information(
            this, "Utilisateur",
            "Sélectionnez un utilisateur à afficher."
            );
        return;
    }

    const QString details = QString(
                                "ID : %1\n"
                                "Nom : %2\n"
                                "Prénom : %3\n"
                                "Mot de passe : %4\n"
                                "Rôle : %5"
                                )
                                .arg(valeurCellule(ligne, 0))
                                .arg(valeurCellule(ligne, 1))
                                .arg(valeurCellule(ligne, 2))
                                .arg(valeurCellule(ligne, 3))
                                .arg(valeurCellule(ligne, 4));

    QMessageBox::information(this, "Détails utilisateur", details);
}

void gutilisateur::trierUtilisateurs()
{
    if (table->rowCount() < 2)
        return;

    QList<QStringList> lignes;

    for (int ligne = 0; ligne < table->rowCount(); ++ligne) {
        QStringList donnees;
        for (int colonne = 0; colonne < 5; ++colonne)
            donnees << valeurCellule(ligne, colonne);
        lignes.append(donnees);
    }

    std::sort(
        lignes.begin(), lignes.end(),
        [](const QStringList &a, const QStringList &b) {
            const QString nomA = a.value(1).toLower();
            const QString nomB = b.value(1).toLower();

            if (nomA == nomB)
                return a.value(2).toLower() < b.value(2).toLower();

            return nomA < nomB;
        }
        );

    for (int ligne = 0; ligne < lignes.size(); ++ligne) {
        for (int colonne = 0; colonne < 5; ++colonne) {
            if (table->item(ligne, colonne))
                table->item(ligne, colonne)->setText(lignes[ligne][colonne]);
        }
    }

    QMessageBox::information(
        this, "Tri",
        "Les utilisateurs ont été triés par Nom puis Prénom."
        );
}

void gutilisateur::rechercherParId()
{
    bool ok = false;

    const QString id = QInputDialog::getText(
                           this,
                           "Recherche par ID",
                           "ID utilisateur :",
                           QLineEdit::Normal,
                           QString(),
                           &ok
                           ).trimmed();

    if (!ok || id.isEmpty())
        return;

    for (int ligne = 0; ligne < table->rowCount(); ++ligne) {
        if (valeurCellule(ligne, 0).compare(id, Qt::CaseInsensitive) == 0) {
            table->selectRow(ligne);
            table->scrollToItem(table->item(ligne, 0));
            return;
        }
    }

    QMessageBox::information(
        this, "Recherche",
        "Aucun utilisateur trouvé avec cet ID."
        );
}

void gutilisateur::exporterPDF()
{
    QString fichier = QFileDialog::getSaveFileName(
        this,
        "Exporter les utilisateurs en PDF",
        "utilisateurs.pdf",
        "Fichier PDF (*.pdf)"
        );

    if (fichier.isEmpty())
        return;

    QPdfWriter pdf(fichier);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageOrientation(QPageLayout::Landscape);
    pdf.setResolution(96);

    QPainter painter(&pdf);

    if (!painter.isActive()) {
        QMessageBox::critical(
            this, "Export PDF",
            "Impossible de créer le PDF."
            );
        return;
    }

    const int gauche = 35;
    const int largeur = pdf.width() - 70;
    const int hauteurLigne = 32;
    int y = 45;

    painter.setPen(QColor("#651522"));
    painter.setFont(QFont("Georgia", 20, QFont::Bold));
    painter.drawText(
        QRect(gauche, y, largeur, 40),
        Qt::AlignCenter,
        "ChéChic - Gestion des utilisateurs"
        );

    y += 45;
    painter.setFont(QFont("Arial", 8));
    painter.setPen(QColor("#555555"));
    painter.drawText(
        QRect(gauche, y, largeur, 25),
        Qt::AlignCenter,
        QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm")
        );

    y += 40;

    const int largeurs[5] = {
        static_cast<int>(largeur * 0.12),
        static_cast<int>(largeur * 0.20),
        static_cast<int>(largeur * 0.20),
        static_cast<int>(largeur * 0.25),
        static_cast<int>(largeur * 0.23)
    };

    painter.setBrush(QColor("#651522"));
    painter.setPen(Qt::NoPen);
    painter.drawRect(gauche, y, largeur, hauteurLigne);

    const QStringList titres = {
        "ID", "Nom", "Prénom", "Mot de passe", "Rôle"
    };

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 8, QFont::Bold));

    int x = gauche;
    for (int colonne = 0; colonne < 5; ++colonne) {
        painter.drawText(
            QRect(x, y, largeurs[colonne], hauteurLigne),
            Qt::AlignCenter,
            titres[colonne]
            );
        x += largeurs[colonne];
    }

    y += hauteurLigne;
    painter.setFont(QFont("Arial", 8));

    for (int ligne = 0; ligne < table->rowCount(); ++ligne) {
        if (y + hauteurLigne > pdf.height() - 40) {
            pdf.newPage();
            y = 40;
        }

        painter.setBrush(QColor("#FFFDF9"));
        painter.setPen(QColor("#D8CEC2"));
        painter.drawRect(gauche, y, largeur, hauteurLigne);
        painter.setPen(QColor("#4B2029"));

        x = gauche;
        for (int colonne = 0; colonne < 5; ++colonne) {
            painter.drawText(
                QRect(
                    x + 3,
                    y + 2,
                    largeurs[colonne] - 6,
                    hauteurLigne - 4
                    ),
                Qt::AlignCenter,
                valeurCellule(ligne, colonne)
                );
            x += largeurs[colonne];
        }

        y += hauteurLigne;
    }

    painter.end();

    QMessageBox::information(
        this, "Export PDF",
        "Le PDF a été créé avec succès."
        );
}

class GraphiqueTravail : public QWidget
{
public:
    GraphiqueTravail(
        const QStringList &noms,
        const QList<double> &heures,
        QWidget *parent = nullptr
        )
        : QWidget(parent),
        m_noms(noms),
        m_heures(heures)
    {
        setMinimumHeight(350);
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(rect(), QColor("#FFFDF9"));

        if (m_heures.isEmpty())
            return;

        const int gauche = 65;
        const int haut = 30;
        const int bas = 65;
        const int droite = 30;
        const int largeurGraphique = width() - gauche - droite;
        const int hauteurGraphique = height() - haut - bas;

        double maximum = 1.0;
        for (double valeur : m_heures)
            maximum = qMax(maximum, valeur);

        painter.setPen(QPen(QColor("#D8CEC2"), 1));
        painter.drawLine(gauche, haut, gauche, haut + hauteurGraphique);
        painter.drawLine(
            gauche,
            haut + hauteurGraphique,
            gauche + largeurGraphique,
            haut + hauteurGraphique
            );

        painter.setFont(QFont("Arial", 8));

        for (int i = 0; i <= 5; ++i) {
            const double valeur = maximum * i / 5.0;
            const int y = haut + hauteurGraphique - (hauteurGraphique * i / 5);

            painter.setPen(QColor("#E5DDD3"));
            painter.drawLine(
                gauche,
                y,
                gauche + largeurGraphique,
                y
                );

            painter.setPen(QColor("#4B2029"));
            painter.drawText(
                QRect(5, y - 10, 50, 20),
                Qt::AlignRight | Qt::AlignVCenter,
                QString::number(valeur, 'f', 1)
                );
        }

        const int nombre = m_heures.size();
        const double largeurCase =
            static_cast<double>(largeurGraphique) / nombre;
        const double largeurBarre = largeurCase * 0.55;

        for (int i = 0; i < nombre; ++i) {
            const double valeur = m_heures[i];
            const double hauteur =
                valeur / maximum * hauteurGraphique;
            const double x =
                gauche + i * largeurCase +
                (largeurCase - largeurBarre) / 2.0;
            const double y =
                haut + hauteurGraphique - hauteur;

            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor("#651522"));
            painter.drawRect(QRectF(x, y, largeurBarre, hauteur));

            painter.setPen(QColor("#551A25"));
            painter.setFont(QFont("Arial", 8, QFont::Bold));
            painter.drawText(
                QRectF(x - 10, y - 22, largeurBarre + 20, 20),
                Qt::AlignCenter,
                QString::number(valeur, 'f', 1)
                );

            painter.setFont(QFont("Arial", 8));
            QString nom = m_noms.value(i);
            if (nom.length() > 10)
                nom = nom.left(10) + "...";

            painter.drawText(
                QRectF(
                    x - 20,
                    haut + hauteurGraphique + 8,
                    largeurBarre + 40,
                    35
                    ),
                Qt::AlignCenter,
                nom
                );
        }
    }

private:
    QStringList m_noms;
    QList<double> m_heures;
};

void gutilisateur::afficherStatistiques()
{
    if (table->rowCount() == 0) {
        QMessageBox::information(
            this,
            "Statistiques",
            "Aucun utilisateur disponible."
            );
        return;
    }

    for (int ligne = 0; ligne < table->rowCount(); ++ligne) {
        const QString id = valeurCellule(ligne, 0);
        bool ok = false;

        const double heures = QInputDialog::getDouble(
            this,
            "Temps de travail",
            QString("Heures travaillées pour %1 %2 :")
                .arg(valeurCellule(ligne, 2))
                .arg(valeurCellule(ligne, 1)),
            tempsTravail.value(id, 0.0),
            0.0,
            10000.0,
            1,
            &ok
            );

        if (ok)
            tempsTravail[id] = heures;
    }

    QDialog dialogue(this);
    dialogue.setWindowTitle("Statistiques des utilisateurs");
    dialogue.resize(820, 520);
    dialogue.setStyleSheet("background-color: #F8F4EE;");

    auto *layout = new QVBoxLayout(&dialogue);

    auto *titre = new QLabel(
        "Temps de travail des utilisateurs",
        &dialogue
        );
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "color: #551A25;"
        "font-size: 20px;"
        "font-weight: bold;"
        );
    layout->addWidget(titre);

    QStringList noms;
    QList<double> heures;

    for (int ligne = 0; ligne < table->rowCount(); ++ligne) {
        const QString id = valeurCellule(ligne, 0);
        noms << valeurCellule(ligne, 1);
        heures << tempsTravail.value(id, 0.0);
    }

    auto *graphique = new GraphiqueTravail(
        noms,
        heures,
        &dialogue
        );
    layout->addWidget(graphique, 1);

    auto *fermer = new QPushButton("Fermer", &dialogue);
    fermer->setFixedHeight(45);
    fermer->setStyleSheet(QUIT_STYLE);
    layout->addWidget(fermer, 0, Qt::AlignRight);

    connect(
        fermer,
        &QPushButton::clicked,
        &dialogue,
        &QDialog::accept
        );

    dialogue.exec();
}

void gutilisateur::ouvrirTableauDeBord()
{
    activerMenu(dashboardBtn);
    pageTitle->setText("Tableau de bord");
}

void gutilisateur::ouvrirUtilisateurs()
{
    activerMenu(usersMenu);
    pageTitle->setText("Gestion des utilisateurs");
}

void gutilisateur::ouvrirClients()
{
    activerMenu(clientsBtn);
    pageTitle->setText("Gestion des clients");
}

void gutilisateur::ouvrirCollections()
{
    activerMenu(collectionsBtn);
    pageTitle->setText("Gestion des collections");
}

void gutilisateur::ouvrirFournisseurs()
{
    activerMenu(fournisseursBtn);
    pageTitle->setText("Gestion des fournisseurs");
}

void gutilisateur::ouvrirEquipements()
{
    activerMenu(equipementsBtn);
    pageTitle->setText("Gestion des équipements");
}

void gutilisateur::quitter()
{
    close();
}




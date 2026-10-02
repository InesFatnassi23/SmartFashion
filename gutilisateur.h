#ifndef GUTILISATEUR_H
#define GUTILISATEUR_H

#include <QMainWindow>
#include <QString>
#include <QMap>

class QLineEdit;
class QComboBox;
class QTableWidget;
class QPushButton;
class QLabel;

class gutilisateur : public QMainWindow
{
    Q_OBJECT

public:
    explicit gutilisateur(QWidget *parent = nullptr);

private slots:

    // =====================================================
    // CRUD UTILISATEURS
    // =====================================================

    void ajouterUtilisateur();
    void modifierUtilisateur();
    void supprimerUtilisateur();
    void afficherUtilisateur();
    void selectionnerUtilisateur();
    void quitter();

    // =====================================================
    // NOUVELLES FONCTIONNALITES
    // =====================================================

    // Tri par Nom puis Prénom
    void trierUtilisateurs();

    // Recherche par ID
    void rechercherParId();

    // Export PDF
    void exporterPDF();

    // Statistiques graphiques du temps de travail
    void afficherStatistiques();

    // =====================================================
    // MENU
    // =====================================================

    void ouvrirTableauDeBord();
    void ouvrirUtilisateurs();
    void ouvrirClients();
    void ouvrirCollections();
    void ouvrirFournisseurs();
    void ouvrirEquipements();

private:

    // =====================================================
    // CHAMPS DU FORMULAIRE
    // =====================================================

    QLineEdit *idEdit;
    QLineEdit *nomEdit;
    QLineEdit *prenomEdit;
    QLineEdit *passwordEdit;

    QComboBox *roleCombo;

    // =====================================================
    // TABLEAU
    // =====================================================

    QTableWidget *table;

    // =====================================================
    // BOUTONS CRUD
    // =====================================================

    QPushButton *ajouterBtn;
    QPushButton *modifierBtn;
    QPushButton *supprimerBtn;
    QPushButton *afficherBtn;
    QPushButton *quitterBtn;

    // =====================================================
    // BOUTONS NOUVELLES FONCTIONNALITES
    // =====================================================

    QPushButton *trierBtn;
    QPushButton *rechercherBtn;
    QPushButton *pdfBtn;
    QPushButton *statistiquesBtn;

    // =====================================================
    // BOUTONS MENU
    // =====================================================

    QPushButton *dashboardBtn;
    QPushButton *usersMenu;
    QPushButton *clientsBtn;
    QPushButton *collectionsBtn;
    QPushButton *fournisseursBtn;
    QPushButton *equipementsBtn;

    // =====================================================
    // TITRE
    // =====================================================

    QLabel *pageTitle;

    // =====================================================
    // TEMPS DE TRAVAIL
    // ID utilisateur -> nombre d'heures
    // =====================================================

    QMap<QString, double> tempsTravail;

    // =====================================================
    // FONCTIONS UTILITAIRES
    // =====================================================

    void activerMenu(QPushButton *boutonActif);

    bool idExiste(
        const QString &id,
        int ligneIgnoree = -1
        ) const;

    void viderFormulaire();

    QString valeurCellule(
        int ligne,
        int colonne
        ) const;
};

#endif // GUTILISATEUR_H
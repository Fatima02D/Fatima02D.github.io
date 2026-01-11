# Phase 1 - Montage, Câblage et Contrôle Moteur de Base

## 📋 Vue d'ensemble

**Objectif**: Assembler la plateforme mobile et implémenter les mouvements de base avec contrôle PWM stable.

**Durée estimée**: 3-4 semaines (30 min/jour)

**Statut**: 🟡 En cours / 🟢 Complété / ⚪ Non commencé

---

## 🎯 Objectifs Spécifiques

### Objectifs Techniques
- ✅ Assembler le châssis du robot avec moteurs DC
- ✅ Câbler correctement le driver L298N avec Arduino Uno / STM32
- ✅ Implémenter le contrôle PWM pour les moteurs
- ✅ Tester les mouvements: avancer, reculer, tourner gauche/droite
- ✅ Calibrer les vitesses pour un mouvement stable

### Objectifs d'Apprentissage
- Comprendre le fonctionnement d'un pont en H (L298N)
- Maîtriser le contrôle PWM sur microcontrôleur
- Apprendre à alimenter un système robotique de façon sécuritaire
- Développer des compétences en débogage hardware

---

## 🔬 Question Scientifique

**Question principale**: Quelle est la relation entre le signal PWM appliqué et la vitesse réelle du robot?

**Hypothèse**: La vitesse du robot augmente de manière approximativement linéaire avec la valeur PWM, mais avec un seuil minimal avant que les moteurs ne commencent à tourner (zone morte).

**Méthode de Vérification**:
1. Mesurer la distance parcourue en 3 secondes pour différentes valeurs PWM (50, 100, 150, 200, 255)
2. Calculer la vitesse moyenne (cm/s) pour chaque valeur
3. Tracer le graphique: PWM vs Vitesse
4. Analyser la linéarité et identifier le PWM minimal fonctionnel (seuil de démarrage)
5. Calculer l'équation de la droite de tendance

---

## 🛠️ Matériel Nécessaire

| Composant | Quantité | Spécifications | Prix (CAD) | Fournisseur Suggéré |
|-----------|----------|----------------|------------|---------------------|
| Arduino Uno R3 / STM32 | 1 | ATmega328P, 5V ou STM32F103 | $25-30 | RobotShop.ca |
| Driver L298N | 1 | 2A par canal, 5-35V | $8 | Amazon.ca |
| Moteurs DC | 2 | 6V, avec encodeurs optionnels | $15 | AliExpress |
| Roues | 2 | 65mm diamètre | $5 | Amazon.ca |
| Châssis 2WD | 1 | Acrylique ou aluminium | $15 | RobotShop.ca |
| Batterie Li-Po | 1 | 7.4V, 2200mAh | $20 | HobbyKing |
| Câbles Dupont | 20 | M-M, M-F | $3 | Amazon.ca |
| Ruban adhésif | 1 | Électrique | $2 | Dollarama |

**Total estimé**: ~$93-98 CAD

---

## 🔌 Schéma de Câblage

```
Arduino Uno / STM32    L298N Driver          Moteurs DC
-----------------      -------------          ----------
    5V    ---------> VCC (Logic)
   GND    ---------> GND
    D5    ---------> ENA (PWM Moteur A)
    D6    ---------> ENB (PWM Moteur B)
    D7    ---------> IN1 (Direction A)
    D8    ---------> IN2 (Direction A)
    D9    ---------> IN3 (Direction B)
   D10    ---------> IN4 (Direction B)

                     OUT1 -------------> Moteur Gauche +
                     OUT2 -------------> Moteur Gauche -
                     OUT3 -------------> Moteur Droit +
                     OUT4 -------------> Moteur Droit -

Batterie 7.4V -----> 12V (Power Input)
                     GND (commun avec Arduino)
```

**⚠️ Points de Sécurité Critiques**:
- ❌ **Ne jamais** connecter la batterie directement à l'Arduino (risque de griller le microcontrôleur)
- ✅ **Toujours** vérifier la polarité avant de brancher la batterie
- ✅ Utiliser un interrupteur sur le fil positif de la batterie
- ✅ Vérifier que **GND est commun** entre Arduino et L298N
- ✅ Tester d'abord avec alimentation USB (sans moteurs) avant d'utiliser la batterie

---

## 💻 Code de Base

### Version 1: Test Simple des Moteurs

```cpp
/*
 * Phase 1 - Contrôle Moteur de Base
 * Auteur: [Votre Nom]
 * Date: [Date]
 * Description: Programme de test pour contrôler deux moteurs DC
 *              via un driver L298N avec PWM
 */

// ========== CONFIGURATION DES PINS ==========
// Pins de contrôle moteur gauche
const int ENA = 5;    // PWM pour vitesse moteur gauche
const int IN1 = 7;    // Direction moteur gauche
const int IN2 = 8;

// Pins de contrôle moteur droit
const int ENB = 6;    // PWM pour vitesse moteur droit
const int IN3 = 9;    // Direction moteur droit
const int IN4 = 10;

void setup() {
  // Configuration des pins en sortie
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Initialisation de la communication série pour debug
  Serial.begin(9600);
  Serial.println("=== Robot Initialisé ===");
  Serial.println("Test de base des moteurs");
}

void loop() {
  // Séquence de test
  Serial.println("\n--- Test Avancer ---");
  avancer(200);  // Avancer à vitesse 200/255
  delay(2000);   // Pendant 2 secondes
  
  arreter();
  delay(1000);
  
  Serial.println("\n--- Test Reculer ---");
  reculer(200);
  delay(2000);
  
  arreter();
  delay(1000);
  
  Serial.println("\n--- Test Rotation Gauche ---");
  tournerGauche(150);
  delay(1000);
  
  arreter();
  delay(1000);
  
  Serial.println("\n--- Test Rotation Droite ---");
  tournerDroite(150);
  delay(1000);
  
  arreter();
  delay(3000);  // Pause de 3 secondes avant de recommencer
}

// ========== FONCTIONS DE MOUVEMENT ==========

/**
 * Fait avancer le robot
 * @param vitesse: Valeur PWM (0-255)
 */
void avancer(int vitesse) {
  // Limiter la vitesse entre 0 et 255
  vitesse = constrain(vitesse, 0, 255);
  
  // Moteur gauche avance
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, vitesse);
  
  // Moteur droit avance
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, vitesse);
  
  Serial.print("Avancer - Vitesse PWM: ");
  Serial.println(vitesse);
}

/**
 * Fait reculer le robot
 * @param vitesse: Valeur PWM (0-255)
 */
void reculer(int vitesse) {
  vitesse = constrain(vitesse, 0, 255);
  
  // Moteur gauche recule
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, vitesse);
  
  // Moteur droit recule
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, vitesse);
  
  Serial.print("Reculer - Vitesse PWM: ");
  Serial.println(vitesse);
}

/**
 * Fait tourner le robot vers la gauche (rotation sur place)
 * @param vitesse: Valeur PWM (0-255)
 */
void tournerGauche(int vitesse) {
  vitesse = constrain(vitesse, 0, 255);
  
  // Moteur gauche recule, moteur droit avance
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, vitesse);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, vitesse);
  
  Serial.print("Tourner Gauche - Vitesse PWM: ");
  Serial.println(vitesse);
}

/**
 * Fait tourner le robot vers la droite (rotation sur place)
 * @param vitesse: Valeur PWM (0-255)
 */
void tournerDroite(int vitesse) {
  vitesse = constrain(vitesse, 0, 255);
  
  // Moteur gauche avance, moteur droit recule
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, vitesse);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, vitesse);
  
  Serial.print("Tourner Droite - Vitesse PWM: ");
  Serial.println(vitesse);
}

/**
 * Arrête complètement le robot
 */
void arreter() {
  // Désactiver tous les moteurs
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  Serial.println("ARRÊT");
}
```

---

## 🧪 Protocole Expérimental

### Expérience 1: Relation PWM-Vitesse

**Matériel supplémentaire nécessaire**:
- Ruban à mesurer (3 mètres minimum)
- Chronomètre (ou smartphone)
- Surface plane et lisse (carrelage, plancher de bois)
- Ruban adhésif pour marquer la ligne de départ

**Procédure Détaillée**:

1. **Préparation**:
   - Charger complètement la batterie (vérifier voltage ≈ 8.4V pour Li-Po 2S)
   - Marquer une ligne de départ claire au sol
   - Préparer le chronomètre

2. **Pour chaque valeur de PWM** (50, 100, 150, 200, 255):
   
   a. Placer le robot sur la ligne de départ, bien aligné
   
   b. Démarrer le chronomètre et le robot **simultanément**
   
   c. Laisser le robot avancer pendant **exactement 3.00 secondes**
   
   d. Arrêter le robot et marquer sa position finale
   
   e. Mesurer la distance parcourue en centimètres (en ligne droite depuis le départ)
   
   f. **Répéter 3 fois** pour avoir des données fiables
   
   g. Noter la tension de la batterie avant chaque série

3. **Saisie des données**:
   - Remplir le tableau ci-dessous
   - Calculer les moyennes et écarts-types

**Tableau de Données Brutes**:

| PWM | Tension Bat. (V) | Essai 1 (cm) | Essai 2 (cm) | Essai 3 (cm) | Moyenne (cm) | Écart-type (cm) | Vitesse (cm/s) |
|-----|------------------|--------------|--------------|--------------|--------------|-----------------|----------------|
| 50  |                  |              |              |              |              |                 |                |
| 100 |                  |              |              |              |              |                 |                |
| 150 |                  |              |              |              |              |                 |                |
| 200 |                  |              |              |              |              |                 |                |
| 255 |                  |              |              |              |              |                 |                |

**Calculs à Effectuer**:

1. **Vitesse moyenne**:
   ```
   Vitesse (cm/s) = Distance moyenne (cm) / 3.00 s
   ```

2. **Écart-type** (mesure de la variabilité):
   ```
   σ = √[Σ(xi - x̄)² / n]
   ```
   Où:
   - xi = valeur individuelle
   - x̄ = moyenne
   - n = nombre d'essais (3)

3. **Coefficient de variation** (CV):
   ```
   CV (%) = (écart-type / moyenne) × 100%
   ```
   Un CV < 10% indique une bonne répétabilité

---

## 📊 Résultats Attendus

### Graphique 1: PWM vs Vitesse

**À tracer dans Excel ou Python**:

```
Vitesse (cm/s)
    ^
 60 |                               ●
    |                          ●
 40 |                     ●
    |               ●
 20 |          ●
    |     ●_________  (Zone morte)
  0 +----+----+----+----+----+-----> PWM
    0   50  100  150  200  250
```

**Caractéristiques attendues**:
- **Zone morte**: PWM < 60-80 (les moteurs ne tournent pas assez fort)
- **Zone linéaire**: PWM 80-255 (relation approximativement linéaire)
- **Équation**: v = a × PWM + b
  - Où `a` est la pente et `b` est l'ordonnée à l'origine
- **Coefficient R²**: devrait être > 0.95 pour une bonne linéarité

### Observations Prévues

1. **PWM minimal fonctionnel**: Identifier le seuil au-dessus duquel les moteurs commencent à tourner de façon fiable

2. **Linéarité**: Vérifier si la relation est vraiment linéaire ou s'il y a des non-linéarités

3. **Répétabilité**: Vérifier la constance des mesures (écart-type faible)

4. **Influence de la batterie**: Noter si la tension de batterie affecte significativement les résultats

---

## 🔍 Problèmes Courants et Solutions

### Problème 1: Les Moteurs Ne Tournent Pas

**Symptôme**: Aucun mouvement même avec PWM = 255

**Causes possibles**:
1. ❌ Batterie déchargée
   - **Solution**: Vérifier voltage batterie (doit être > 6.5V pour une 2S Li-Po)
   - Utiliser un multimètre

2. ❌ Câblage incorrect
   - **Solution**: Revoir le schéma de connexion
   - Vérifier chaque connexion avec un multimètre

3. ❌ Problème avec le driver L298N
   - **Solution**: Vérifier les LED du L298N (doivent s'allumer)
   - Tester la continuité des sorties

4. ❌ Code incorrect
   - **Solution**: Vérifier que les pins correspondent au câblage
   - Utiliser Serial.print() pour déboguer

---

### Problème 2: Robot Tourne en Avançant

**Symptôme**: Le robot dévie de sa trajectoire rectiligne

**Cause**: Les deux moteurs ne tournent pas à la même vitesse (différences mécaniques)

**Solutions**:

1. **Calibration logicielle** (recommandé pour Phase 1):
   ```cpp
   void avancer(int vitesse) {
     // Exemple: moteur droit 5% plus lent
     analogWrite(ENA, vitesse);
     analogWrite(ENB, vitesse * 0.95);  // Facteur de correction
   }
   ```

2. **Ajustement mécanique**:
   - Vérifier l'alignement des roues
   - S'assurer que les roues ont la même friction
   - Vérifier que les essieux sont droits

3. **Note pour Phase 2**: Les encodeurs permettront une calibration automatique précise

---

### Problème 3: Mouvement Saccadé

**Symptôme**: Le robot avance par à-coups

**Causes possibles**:
1. ❌ Surface trop rugueuse
   - **Solution**: Tester sur surface lisse (carrelage)

2. ❌ Batterie faible
   - **Solution**: Recharger ou remplacer

3. ❌ PWM trop bas
   - **Solution**: Utiliser PWM ≥ 100

4. ❌ Mauvais contact électrique
   - **Solution**: Vérifier toutes les connexions, resserrer les vis

---

### Problème 4: Moteurs S'arrêtent Après Quelques Secondes

**Cause**: Protection thermique du L298N activée (surchauffe)

**Solutions**:
- Réduire le PWM (commencer à 150 au lieu de 255)
- Ajouter un dissipateur thermique sur le L298N
- Limiter la durée de fonctionnement continu
- Vérifier qu'il n'y a pas de court-circuit

---

## ✅ Critères de Succès

| Critère | Objectif Cible | Méthode de Mesure |
|---------|---------------|-------------------|
| **Trajectoire rectiligne** | Déviation < 15° sur 1 mètre | Mesure de l'angle avec rapporteur |
| **Contrôle de vitesse** | 3 vitesses distinctes fonctionnelles | Tests à PWM 100, 150, 200 |
| **Rotation précise** | Tour 360° avec erreur ± 30° | Marquage au sol + mesure |
| **Stabilité mécanique** | Pas de vibrations excessives | Observation visuelle |
| **Autonomie** | > 20 minutes de fonctionnement | Chronométrage avec batterie pleine |
| **Répétabilité** | Écart-type < 10% de la moyenne | Calcul statistique sur 3 essais |

---

## 📚 Ressources d'Apprentissage

### Tutoriels Recommandés

1. **How To Mechatronics - Arduino DC Motor Control**
   - Lien: https://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/
   - Durée: ~30 minutes
   - **Focus**: Comprendre le fonctionnement du L298N

2. **Instructables - 4WD Robot Car**
   - Lien: https://www.instructables.com/4WD-Robot-Car-Using-L298N/
   - Durée: ~1 heure
   - **Focus**: Assemblage mécanique et tests

3. **Arduino Documentation - analogWrite()**
   - Lien: https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
   - **Focus**: Comprendre le PWM

### Concepts Théoriques à Maîtriser

1. **PWM (Pulse Width Modulation)**
   - Principe: Contrôle de puissance par rapport cyclique
   - Fréquence Arduino: ~490 Hz (pins 5 et 6), ~980 Hz (autres pins)
   - Résolution: 8 bits (0-255)

2. **Pont en H (H-Bridge)**
   - Permet l'inversion de polarité
   - Contrôle bidirectionnel des moteurs
   - Protection contre les courts-circuits

3. **Couple vs Vitesse (Moteurs DC)**
   - Relation inverse: couple élevé = vitesse faible
   - Courbe caractéristique du moteur

4. **Alimentation et Régulation**
   - Importance de la régulation de tension
   - Capacités de découplage
   - GND commun (référence unique)

---

## 📝 Documentation à Produire (Pour Portfolio)

### 1. Photos Requises (Haute Qualité, Bonne Lumière)

**Assemblage**:
- [ ] Châssis complet (vue du dessus)
- [ ] Châssis complet (vue de côté)
- [ ] Câblage L298N (clair et net, tous les fils visibles)
- [ ] Connexions Arduino-L298N (gros plan)

**Fonctionnement**:
- [ ] Robot en mouvement (avancer)
- [ ] Robot en rotation
- [ ] Setup expérimental (ruban à mesurer, ligne de départ)

### 2. Vidéos de Démonstration (15-30 secondes chacune)

- [ ] Robot avançant en ligne droite sur 1 mètre
- [ ] Robot effectuant une rotation 360° sur place
- [ ] Démonstration des 4 mouvements de base (avant, arrière, gauche, droite)
- [ ] Test de vitesse variable (PWM 100 → 255)

### 3. Données Expérimentales

- [ ] Tableau PWM vs Vitesse complété avec toutes les mesures
- [ ] Graphique Excel ou Python (PWM vs Vitesse) avec courbe de tendance
- [ ] Équation de la droite de régression
- [ ] Coefficient R²
- [ ] Photos du setup de mesure

### 4. Code Source

- [ ] Code Arduino/STM32 bien commenté
- [ ] Hébergé sur GitHub
- [ ] README avec:
  - Description du projet
  - Instructions de compilation
  - Schéma de câblage
  - Dépendances (si applicable)

---

## 🎯 Préparation pour la Phase 2

Une fois la Phase 1 complétée avec succès:

**Vérifications finales**:
1. ✅ Tous les critères de succès atteints
2. ✅ Documentation complète (photos, vidéos, données)
3. ✅ Code uploadé sur GitHub
4. ✅ Problèmes connus documentés

**Transition vers Phase 2**:

La **Phase 2** introduira les **encodeurs** pour mesurer précisément la vitesse et la distance parcourue. Cette amélioration permettra:

- Mesure exacte de la vitesse réelle (vs PWM)
- Correction automatique des différences entre moteurs
- Déplacement rectiligne précis sans déviation
- Base pour l'odométrie (Phase 6)

**Matériel supplémentaire nécessaire pour Phase 2**:
- Encodeurs rotatifs (2x)
- Résistances pull-up si nécessaire
- Câbles pour connexion aux pins d'interruption

---

## 💡 Notes et Observations Personnelles

_Utilisez cet espace pour documenter votre expérience pendant le projet_:

**Date de début**: _______________

**Défis rencontrés**:
- 
- 
- 

**Solutions trouvées**:
- 
- 
- 

**Améliorations possibles**:
- 
- 
- 

**Questions à explorer**:
- 
- 
- 

**Temps total investi**: _____ heures

---

## 📋 Checklist de Complétion

Avant de passer à la Phase 2, assurez-vous d'avoir:

**Technique**:
- [ ] Robot assemblé et fonctionnel
- [ ] Les 4 mouvements de base opérationnels
- [ ] Expérience PWM-Vitesse complétée
- [ ] Tous les critères de succès validés

**Documentation**:
- [ ] Photos du robot (minimum 6)
- [ ] Vidéos de démonstration (minimum 3)
- [ ] Tableau de données rempli
- [ ] Graphique généré et analysé
- [ ] Code commenté et uploadé sur GitHub

**Réflexion**:
- [ ] Problèmes documentés avec solutions
- [ ] Apprentissages notés
- [ ] Questions pour Phase 2 identifiées

---

**Signature de complétion**: ________________  
**Date**: __________

---

*Ce document fait partie du projet "Plateforme Robotique Mobile Autonome"*  
*Auteur: [Votre Nom]*  
*Version: 1.0*  
*Dernière mise à jour: [Date]*

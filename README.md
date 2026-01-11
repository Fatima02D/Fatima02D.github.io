# Fatima02D.github.io
Robotics &amp; Mechatronics Portfolio

# 🤖 Plateforme Robotique Mobile Autonome

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://img.shields.io/badge/build-in%20progress-orange)]()
[![Documentation](https://img.shields.io/badge/docs-in%20progress-blue)]()

> Conception et développement d'une plateforme robotique mobile autonome, pensée comme un système modulaire et évolutif. Un projet d'apprentissage technique structuré en 8 phases progressives.

**Portfolio en ligne**: [https://fatima02d.github.io](https://fatima02d.github.io)

---

## 📖 Table des Matières

- [Vue d'ensemble](#vue-densemble)
- [Objectifs du Projet](#objectifs-du-projet)
- [Architecture Système](#architecture-système)
- [Phases du Projet](#phases-du-projet)
- [Matériel Utilisé](#matériel-utilisé)
- [Stack Logiciel](#stack-logiciel)
- [Installation](#installation)
- [Documentation](#documentation)
- [Évolutions Futures](#évolutions-futures)
- [Licence](#licence)
- [Contact](#contact)

---

## 🎯 Vue d'ensemble

Ce projet consiste en la conception et le développement d'une plateforme robotique mobile autonome, développée par étapes et intégrant progressivement :

- ✅ Commande des moteurs avec contrôle PWM
- ✅ Calibration par encodeurs
- ✅ Communication inter-modules (I2C)
- 📋 Navigation autonome
- 📋 Évitement d'obstacles
- 📋 Manipulation d'objets

**Objectif final**: Concevoir un système capable de se déplacer de manière fiable entre des points définis, d'interagir avec son environnement et d'exécuter des tâches simples de façon autonome.

---

## 💡 Objectifs du Projet

### Objectifs Techniques
- Maîtriser la conception de systèmes mécatroniques complets
- Développer des compétences en programmation embarquée (C/C++, Python)
- Comprendre les principes de contrôle en boucle fermée (PID)
- Implémenter des algorithmes de navigation autonome
- Intégrer plusieurs sous-systèmes (capteurs, actionneurs, communication)

### Approche Méthodologique
Chaque phase du projet est structurée autour de :
- **Objectif technique clair**
- **Question scientifique à explorer**
- **Méthode expérimentale** avec données mesurables
- **Documentation rigoureuse** des résultats

### Contexte
Projet personnel d'apprentissage réalisé dans le cadre de ma formation en **génie mécanique - mécatronique**, visant à renforcer mes compétences pratiques et ma compréhension des systèmes robotiques.

---

## 🏗️ Architecture Système

```
┌─────────────────────────────────────────────────────────────┐
│              PLATEFORME ROBOTIQUE MOBILE AUTONOME            │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│  ┌──────────────┐      ┌──────────────┐                    │
│  │   Raspberry  │      │  STM32 /     │                    │
│  │      Pi      │◄────►│   Arduino    │                    │
│  │  (Navigation)│ I2C  │  (Contrôle)  │                    │
│  └──────┬───────┘      └──────┬───────┘                    │
│         │                     │                             │
│         │                     ├─────► L298N ──► Moteurs DC  │
│         │                     ├─────► Servos ──► Bras       │
│         │                     └─────► Capteurs              │
│         │                                                    │
│         └──────► ESP32 ◄────── Manette Xbox                 │
│                  (Contrôle distant)                          │
│                                                              │
│  CAPTEURS:                                                   │
│  ├─ Encodeurs moteurs (odométrie)                           │
│  ├─ HC-SR04 Ultrason (détection obstacles)                  │
│  └─ Capteurs IR (suivi de ligne)                            │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

---

## 🚀 Phases du Projet

### Phase 1: Montage & Contrôle Moteur ⚙️

**Statut**: 🔄 En cours

**Objectif**: Assembler la plateforme mobile et implémenter les mouvements de base avec contrôle PWM stable.

**Question scientifique**: Quelle est la relation entre le PWM appliqué et la vitesse réelle du robot?

**Technologies**:
- Arduino Uno / STM32
- Driver L298N
- Moteurs DC
- Langage: C/C++

**Résultats attendus**:
- Caractérisation de la relation PWM-vitesse
- Identification du seuil PWM minimal
- Contrôle fiable des 4 mouvements de base (avant, arrière, gauche, droite)

📊 [Documentation détaillée →](docs/phase1/)

---

### Phase 2: Calibration Encodeurs 📐

**Statut**: 📅 Planifié

**Objectif**: Synchroniser les moteurs pour un déplacement rectiligne précis avec feedback des encodeurs.

**Question scientifique**: La calibration réduit-elle l'erreur de trajectoire du robot?

**Technologies**:
- Encodeurs rotatifs
- Interruptions matérielles
- Contrôle PID

**Résultats attendus**:
- Réduction mesurable de l'erreur de trajectoire
- Déplacement rectiligne sur 2+ mètres
- Synchronisation des vitesses des deux moteurs

📊 [Documentation détaillée →](docs/phase2/)

---

### Phase 3: Contrôle Xbox (I2C) 🎮

**Statut**: 📅 Planifié

**Objectif**: Contrôler manuellement le robot via manette Xbox avec communication ESP32-Arduino.

**Question scientifique**: Quel est le délai entre une commande utilisateur et la réponse du robot?

**Technologies**:
- ESP32 (Bluetooth)
- Communication I2C
- Manette Xbox

**Résultats attendus**:
- Latence mesurée < 100ms
- Contrôle fluide et réactif
- Taux de perte de paquets < 1%

📊 [Documentation détaillée →](docs/phase3/)

---

### Phase 4: Suivi de Ligne 🛤️

**Statut**: 📅 Planifié

**Objectif**: Permettre au robot de suivre une trajectoire définie au sol automatiquement.

**Question scientifique**: Comment la vitesse influence-t-elle la stabilité du suivi de ligne?

**Technologies**:
- Capteurs IR (ligne noire/blanche)
- Contrôle PID

**Résultats attendus**:
- Vitesse optimale identifiée
- Taux de réussite > 90%
- Stabilité en courbes

📊 [Documentation détaillée →](docs/phase4/)

---

### Phase 5: Évitement d'Obstacles 🚧

**Statut**: 📅 Planifié

**Objectif**: Détecter et éviter des obstacles automatiquement sans collision.

**Question scientifique**: Quelle distance seuil minimise le nombre de collisions?

**Technologies**:
- Capteur ultrason HC-SR04
- Algorithme d'évitement

**Résultats attendus**:
- Distance seuil optimale déterminée
- Zéro collision sur parcours test
- Temps de réaction < 200ms

📊 [Documentation détaillée →](docs/phase5/)

---

### Phase 6: Navigation Autonome A→B 🗺️

**Statut**: 📅 Planifié

**Objectif**: Permettre au robot de connaître sa position et atteindre un point cible précis.

**Question scientifique**: Comment l'erreur de position évolue-t-elle avec la distance parcourue?

**Technologies**:
- Odométrie par encodeurs
- Python (Raspberry Pi)
- Calculs de position

**Résultats attendus**:
- Erreur de position < 5cm à 3m
- Navigation fiable vers coordonnées définies
- Correction de trajectoire en temps réel

📊 [Documentation détaillée →](docs/phase6/)

---

### Phase 7: Bras Robotique 🦾

**Statut**: 📅 Planifié

**Objectif**: Saisir et déplacer de petits objets avec précision et répétabilité.

**Question scientifique**: Quel est le taux de réussite de la préhension?

**Technologies**:
- Servomoteurs
- Pince imprimée en 3D
- Cinématique inverse

**Résultats attendus**:
- Taux de préhension > 85%
- Répétabilité ±2mm
- Charge utile définie

📊 [Documentation détaillée →](docs/phase7/)

---

### Phase 8: Intégration Finale 🎯

**Statut**: 📅 Planifié

**Objectif**: Intégrer toutes les fonctionnalités en un système autonome complet.

**Question scientifique**: Le système est-il robuste dans différents scénarios?

**Technologies**:
- Machine à états finis (FSM)
- Intégration multi-modules
- Tests de robustesse

**Résultats attendus**:
- Mission autonome complète réussie
- Taux de succès > 80%
- Comportement adaptatif

📊 [Documentation détaillée →](docs/phase8/)

---

## 🔧 Matériel Utilisé

### Contrôleurs
| Composant | Spécifications | Rôle |
|-----------|---------------|------|
| Arduino Uno / STM32 | Microcontrôleur principal | Contrôle moteurs et capteurs |
| Raspberry Pi 4 | 4GB RAM (optionnel) | Navigation haut niveau |
| ESP32 | WiFi/Bluetooth | Contrôle distant |

### Actionneurs
| Composant | Spécifications | Quantité |
|-----------|---------------|----------|
| Moteurs DC | 6V, 200 RPM, avec encodeurs | 2 |
| Driver L298N | Pont en H, 2A/canal | 1 |
| Servomoteurs MG90S | 180°, 1.8kg·cm | 4 |

### Capteurs
| Composant | Spécifications | Usage |
|-----------|---------------|-------|
| HC-SR04 | Ultrason, portée 2-400cm | Détection obstacles |
| Encodeurs rotatifs | Résolution variable | Odométrie |
| Capteurs IR | Détection ligne | Suivi de trajectoire |

### Alimentation & Structure
| Composant | Spécifications |
|-----------|---------------|
| Batterie Li-Po | 7.4V, 2200mAh |
| Châssis 2WD | Acrylique/Aluminium |
| Roues | 65mm diamètre |

**Coût total estimé**: ~150$ CAD

---

## 💻 Stack Logiciel

### Langages de Programmation
- **C/C++**: Firmware Arduino/STM32 (contrôle moteurs, lecture capteurs)
- **Python 3.8+**: Raspberry Pi (navigation, logique autonome)
- **MATLAB**: Analyse de données, visualisations

### Environnement de Développement
- **IDE**: VS Code avec PlatformIO / STM32CubeIDE
- **Contrôle de version**: Git + GitHub
- **Framework**: Arduino / STM32 HAL
- **Communication série**: 115200 baud

### Bibliothèques Clés

**Arduino/STM32**:
```cpp
#include <Wire.h>           // Communication I2C
#include <Servo.h>          // Contrôle servomoteurs
// PID library (à définir)
```

**Python (Raspberry Pi)**:
```python
import RPi.GPIO as GPIO     # Contrôle GPIO
import smbus                # Communication I2C
import numpy as np          # Calculs numériques
import matplotlib.pyplot as plt  # Visualisations
```

### Protocoles de Communication
- **I2C**: Communication Raspberry Pi ↔ Arduino/STM32
- **UART**: Debug et monitoring
- **Bluetooth**: Contrôle Xbox ↔ ESP32

---

## ⚙️ Installation

### Prérequis

**Matériel**:
- Ordinateur avec port USB
- Plateforme robotique assemblée
- Câbles de connexion

**Logiciel**:
```bash
# Arduino IDE ou PlatformIO
# Python 3.8+ (pour Raspberry Pi)
# Git

# Dépendances Python (Raspberry Pi)
pip install RPi.GPIO numpy matplotlib smbus2
```

### Configuration Matérielle

**Connexions L298N ↔ Arduino/STM32**:
```
ENA (PWM Moteur A) → Pin 5
IN1 (Direction A)  → Pin 7
IN2 (Direction A)  → Pin 8
ENB (PWM Moteur B) → Pin 6
IN3 (Direction B)  → Pin 9
IN4 (Direction B)  → Pin 10

Encodeurs:
Encodeur Gauche → Pin 2 (Interruption)
Encodeur Droit  → Pin 3 (Interruption)
```

**Alimentation**:
- Batterie 7.4V → L298N (12V input)
- ⚠️ **GND commun** entre tous les composants
- Arduino alimenté via USB ou 5V du L298N

### Installation du Code

```bash
# Cloner le repository
git clone https://github.com/Fatima02D/Fatima02D.github.io.git
cd Fatima02D.github.io

# Pour Phase 1 (Arduino)
cd firmware/phase1_motor_control
# Ouvrir dans Arduino IDE ou PlatformIO
# Compiler et téléverser

# Pour Raspberry Pi (phases avancées)
cd raspberry_pi/navigation
python3 setup.py install
```

---

## 📚 Documentation

### Structure de la Documentation

```
docs/
├── phase1/
│   ├── README.md              # Objectifs et méthode
│   ├── code_explanation.md    # Explication du code
│   ├── experimental_data/     # Données brutes
│   ├── results.md             # Résultats et analyses
│   └── images/                # Photos et graphiques
├── phase2/
│   └── ...
├── hardware/
│   ├── wiring_diagrams.pdf    # Schémas de câblage
│   ├── bill_of_materials.xlsx # Liste de matériel
│   └── assembly_guide.md      # Guide d'assemblage
└── software/
    ├── api_reference.md       # Référence API
    └── troubleshooting.md     # Dépannage
```

### Ressources Externes

**Tutoriels utilisés**:
- [Arduino DC Motor Control (HowToMechatronics)](https://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/)
- [PID Control Basics](https://www.instructables.com/Arduino-PID-Tutorial/)
- [Robot Odometry Explained](https://automaticaddison.com/robot-odometry-explained/)

**Concepts théoriques**:
- Modulation PWM (Pulse Width Modulation)
- Ponts en H (H-Bridge)
- Contrôle PID
- Odométrie différentielle
- Cinématique directe/inverse

---

## 🔮 Évolutions Futures

### Court Terme (6 mois)
- [ ] Compléter les phases 1-4
- [ ] Implémenter fusion de capteurs (ultrason + IR)
- [ ] Optimiser paramètres PID
- [ ] Documentation complète avec données expérimentales

### Moyen Terme (12 mois)
- [ ] Compléter phases 5-8
- [ ] Ajouter vision par ordinateur (caméra)
- [ ] Implémenter SLAM basique (cartographie)
- [ ] Tester en conditions extérieures

### Long Terme (Explorations)
- [ ] Apprentissage automatique pour préhension adaptative
- [ ] Coordination multi-robots
- [ ] Intégration ROS (Robot Operating System)
- [ ] Applications spécifiques (agriculture, inspection, etc.)

---

## 🤝 Contribution

Ce projet est principalement personnel et éducatif. Cependant, les suggestions et retours sont les bienvenus!

### Comment Contribuer
1. Fork le repository
2. Créer une branche: `git checkout -b feature/amelioration`
3. Commit: `git commit -m 'Ajout fonctionnalité X'`
4. Push: `git push origin feature/amelioration`
5. Ouvrir une Pull Request

### Standards de Code
- Commentaires clairs en français ou anglais
- Suivre le style du code existant
- Documenter les nouvelles fonctionnalités
- Tester avant de soumettre

---

## 📄 Licence

Ce projet est sous licence **MIT** - voir le fichier [LICENSE](LICENSE) pour plus de détails.

**Résumé**: Vous êtes libre d'utiliser, modifier et distribuer ce code, y compris à des fins commerciales, tant que vous incluez la notice de copyright originale.

---

## 📧 Contact

**Saida Fatima-Zahra Diouf**

- **Email**: [saidafatimazahraadiouf@gmail.com](mailto:saidafatimazahraadiouf@gmail.com)
- **LinkedIn**: [saida-fatimatou-zahraa-diouf](https://www.linkedin.com/in/saida-fatimatou-zahraa-diouf)
- **Portfolio**: [https://fatima02d.github.io](https://fatima02d.github.io)
- **GitHub**: [Fatima02D](https://github.com/Fatima02D)

**Formation**: Génie Mécanique - Mécatronique | Université du Québec à Trois-Rivières (UQTR)

---

## 🙏 Remerciements

- **UQTR**: Pour la formation et l'accès aux ressources
- **Communauté Open Source**: Pour les bibliothèques et outils (Arduino, Python, etc.)
- **HowToMechatronics & tutoriels en ligne**: Pour l'apprentissage initial
- **Communauté robotique**: Pour l'inspiration et le partage de connaissances

---

## 📈 Statistiques du Projet

![GitHub last commit](https://img.shields.io/github/last-commit/Fatima02D/Fatima02D.github.io)
![GitHub repo size](https://img.shields.io/github/repo-size/Fatima02D/Fatima02D.github.io)

**Lignes de code** (estimation): ~2,000 (C/C++) + ~800 (Python)  
**Pages de documentation**: En cours de rédaction  
**Phases complétées**: 0/8 (en développement actif)

---

<p align="center">
  <strong>Développé avec 🤖 et rigueur technique</strong>
</p>

<p align="center">
  <i>"Apprendre, concevoir, améliorer - une étape à la fois"</i>
</p>

---

**Dernière mise à jour**: Janvier 2025  
**Version**: 0.1 (Développement initial)

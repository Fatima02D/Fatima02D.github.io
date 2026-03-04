# 🤖 Plateforme Robotique Mobile Autonome

**Projet:** Développement incrémental d'un robot mobile autonome avec capacité de manipulation  
**Programme:** Génie Mécatronique  
**Auteur:** Saida Fatimatou Zahraa Diouf
**Période:** Janvier - Décembre 2026

---

## 📋 Vue d'Ensemble du Projet

Ce projet suit une approche méthodologique en 8 phases pour développer une plateforme robotique mobile autonome capable de navigation intelligente et de manipulation d'objets. L'objectif final est de créer un système intégré combinant:

- **Mobilité autonome** avec localisation précise
- **Navigation planifiée** avec évitement d'obstacles
- **Manipulation** via bras robotique (pick-and-place)
- **Architecture logicielle modulaire** et évolutive

### 🎯 Objectifs Pédagogiques

1. Maîtriser l'intégration hardware-software dans un système mécatronique complet
2. Développer compétences en contrôle de moteurs, odométrie, et navigation
3. Documenter méthodologie d'ingénierie rigoureuse pour portfolio académique/professionnel
4. Appliquer pensée critique et adaptation face aux contraintes techniques

---

## 🗓️ Architecture du Projet (8 Phases)

### ✅ Phase 1: Assemblage Hardware & Analyse (COMPLÉTÉE)
**Status:** ⚠️ Pivot Décidé - Migration vers Chenilles

**Objectifs:**
- Assemblage châssis 2WD avec moteurs TT
- Intégration contrôleur L298N et Arduino Uno
- Tests de mobilité de base
- Validation de viabilité plateforme

**Résultats:**
- ✅ Hardware assemblé et opérationnel
- ✅ Contrôle moteur PWM fonctionnel
- ⚠️ Limitations critiques identifiées:
  - Mouvement erratique (déviation 13.4cm sur 2m)
  - Capacité charge insuffisante (~500g max)
  - Roue folle crée comportement non-reproductible
  - Instabilité structurelle (3-point contact)

**Décision:** Migration vers plateforme à chenilles pour:
- Stabilité améliorée (surface continue vs 3 points)
- Traction 4x supérieure
- Capacité charge 100-300% augmentée
- Contrôle reproductible (skid steering)

**Documentation:** [`docs/Phase1_Technical_Analysis.md`](docs/Phase1_Technical_Analysis.md)

---

### 🔄 Phase 1B: Intégration Châssis Chenilles (EN COURS)
**Status:** 🚧 Acquisition et Migration

**Objectifs:**
- Acquisition kit châssis à chenilles
- Migration composants électroniques (~70% réutilisés)
- Validation mobilité et capacité charge
- Baseline tests pour phases suivantes

**Timeline:** Semaine du 29 janvier 2026

---

### 📅 Phase 2: Contrôle Moteur & Encodeurs (PLANIFIÉE)
**Objectifs:**
- Intégration encodeurs optiques
- Mesure vitesse et distance
- Calibration précise
- Base pour odométrie

**Livrables:**
- Code de lecture encodeurs (interruptions)
- Algorithme conversion pulses → distance/vitesse
- Tests de précision et répétabilité

---

### 📅 Phase 3: Odométrie & Localisation (PLANIFIÉE)
**Objectifs:**
- Estimation position (x, y, θ) en temps réel
- Fusion données encodeurs gauche/droit
- Compensation dérive et glissement
- Interface de visualisation position

**Concepts clés:**
- Modèle cinématique différentiel
- Intégration numérique position
- Correction erreurs cumulatives

---

### 📅 Phase 4: Contrôle de Trajectoire (PLANIFIÉE)
**Objectifs:**
- Implémentation contrôleur PID pour suivi trajectoire
- Point-to-point navigation
- Suivis de lignes/chemins prédéfinis
- Tuning et optimisation performance

**Métriques de succès:**
- Précision position: < 2cm
- Précision orientation: < 3°
- Répétabilité > 95%

---

### 📅 Phase 5: Planification de Chemin (PLANIFIÉE)
**Objectifs:**
- Algorithmes de pathfinding (A*, RRT)
- Représentation environnement (grille/graphe)
- Optimisation trajectoires
- Gestion contraintes cinématiques

---

### 📅 Phase 6: Navigation Autonome (PLANIFIÉE)
**Objectifs:**
- Intégration capteurs (ultrason/IR)
- Évitement obstacles temps-réel
- Re-planification dynamique
- Comportements autonomes (exploration, retour base)

---

### 📅 Phase 7: Intégration Bras Robotique (PLANIFIÉE)
**Objectifs:**
- Montage bras 4-DOF sur plateforme
- Contrôle servomoteurs
- Cinématique inverse pour positionnement
- Interface robot mobile ↔ bras

---

### 📅 Phase 8: Système Pick-and-Place Autonome (PLANIFIÉE)
**Objectifs:**
- Workflow complet: détecter → naviguer → saisir → placer
- Intégration vision (optionnel)
- Coordination mobilité + manipulation
- Démonstration système intégré

---

## 🛠️ Stack Technique

### Hardware
- **Microcontrôleur:** Arduino Elegoo Uno R3 (ATmega328P)
- **Châssis:** Plateforme à chenilles (upgrade Phase 1B)
  - *Précédent:* 2WD bois avec roue folle (Phase 1 - analysé et abandonné)
- **Moteurs:** DC gear motors avec encodeurs
- **Driver Moteur:** L298N Dual H-Bridge
- **Alimentation:** Batterie Li-Po 7.4V, 2000mAh
- **Capteurs (phases futures):**
  - Encodeurs optiques (odométrie)
  - Ultrasons HC-SR04 (évitement obstacles)
  - Potentiellement: IMU, caméra
- **Bras Robotique (Phase 7-8):** 4-DOF servo-actuated arm

### Software
- **IDE:** Arduino IDE / PlatformIO
- **Langage:** C/C++ (Arduino)
- **Librairies principales:**
  - Motor control (PWM, encodeurs)
  - PID control
  - Navigation algorithms
  - Serial communication (debugging/monitoring)
- **Outils de développement:**
  - Git/GitHub (version control)
  - Python (data analysis, visualization)
  - MATLAB/Octave (simulation - optionnel)

### Documentation & Portfolio
- **Site Web:** [fatima02d.github.io](https://fatima02d.github.io)
- **Format:** Markdown (README, analyses techniques)
- **Visualisations:** Graphiques, diagrammes, photos commentées

---

## 📂 Structure du Repository

```
autonomous-robot-platform/
├── README.md                          # Ce fichier
├── docs/
│   ├── Phase1_Technical_Analysis.md   # Analyse détaillée Phase 1
│   ├── Phase1_Test_Results.csv        # Données empiriques tests
│   └── ...                            # Documentation futures phases
├── src/
│   ├── phase1_motor_control/
│   │   ├── basic_pwm_control.ino      # Contrôle moteur de base
│   │   └── motor_test.ino             # Tests mobilité
│   └── ...                            # Code futures phases
├── hardware/
│   ├── schematics/
│   │   ├── motor_driver_wiring.png    # Schéma L298N
│   │   └── ...
│   └── datasheets/
│       ├── L298N_datasheet.pdf
│       ├── TT_motor_specs.pdf
│       └── ...
├── images/
│   ├── phase1/
│   │   ├── chassis_assembled.jpg      # Photos Phase 1
│   │   ├── wiring_detail.jpg
│   │   └── ...
│   └── ...
├── tests/
│   ├── phase1_trajectory_test.csv     # Données test ligne droite
│   ├── phase1_load_test.csv           # Données test charge
│   └── ...
└── tools/
    ├── data_analysis.py               # Scripts analyse Python
    └── visualization.py               # Génération graphiques
```

---

## 📊 Métriques & KPIs

### Phase 1 - Résultats Empiriques

| Métrique | Valeur Mesurée | Requis | Status |
|----------|----------------|--------|--------|
| **Précision trajectoire** | ±13.4cm / 2m | < ±2cm | ❌ Insuffisant |
| **Reproductibilité distance** | ±4.5cm / 2m | < ±1cm | ❌ Insuffisant |
| **Capacité de charge** | ~500g | ≥1000g (avec bras) | ❌ Insuffisant |
| **Stabilité structurelle** | 3-point contact | Surface continue | ❌ Inadéquat |

**Conclusion:** Plateforme 2WD non viable → Migration chenilles décidée

---

## 🎓 Leçons d'Ingénierie - Phase 1

### 1. Validation Précoce des Hypothèses
Tests empiriques en Phase 1 ont révélé limitations *avant* investissement majeur en développement logiciel. **Gain estimé:** 4-6 semaines évitées de debugging de problèmes fondamentalement insolubles.

### 2. Limites de Compensation Logicielle
Algorithmes avancés (PID, calibration extensive) ne peuvent compenser défauts mécaniques fondamentaux:
- Friction asymétrique roue folle
- Capacité charge structurelle insuffisante
- Traction limitée (2WD)

**Principe:** Base mécanique solide + contrôle simple > Base défaillante + contrôle complexe

### 3. Éléments Passifs = Comportement Non-Déterministe
Roue folle (élément passif) introduit:
- Hystérésis directionnelle
- Friction variable
- Impossibilité de reproductibilité

**Solution:** Éliminer éléments passifs → 4WD, chenilles, mecanum wheels

### 4. Décisions Data-Driven vs Emotional Attachment
Données objectives (déviation 13.4cm, limite 500g) justifient pivot malgré temps investi assemblage initial. **ROI décisionnel:** Positif (temps net économisé + qualité finale)

---

## 🚀 Prochaines Étapes

### Court Terme
- [x] Compléter analyse technique Phase 1
- [x] Documenter décision et justification
- [ ] Commander châssis chenilles (Amazon)
- [ ] Réception et inspection composants
- [ ] Migration hardware Phase 1B

### Moyen Terme 
- [ ] Phases 2-4: Contrôle, odométrie, trajectoires
- [ ] Développement stack logiciel de base
- [ ] Tests de validation systématiques

### Long Terme 
- [ ] Phases 5-8: Navigation autonome + manipulation
- [ ] Démonstration système intégré
- [ ] Finalisation documentation portfolio

---

## 📧 Contact & Collaboration

**Auteur:** Saida Fatimatou Zahraa Diouf  
**Institution:** UQTR - Génie Mécatronique  
**Portfolio:** [fatima02d.github.io](https://fatima02d.github.io)  
**GitHub:** [github.com/fatima02d](https://github.com/fatima02d)

---

## 📜 Licence

Ce projet est développé à titre personnel. 
Documentation et code disponibles pour référence éducative.

---

## 🙏 Remerciements

- UQTR - Programme de Génie Mécatronique
- Communauté Arduino et forums robotique
- Ressources open-source (librairies, tutoriels)

---

**Dernière mise à jour:** 22 janvier 2026  
**Version README:** 1.1 (Phase 1 complétée, Phase 1B en préparation)

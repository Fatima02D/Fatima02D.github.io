# Plan de Collecte de Données - Projet Robot Pick & Place

## 📊 Vue d'ensemble

Ce document structure la collecte de données pour les 8 parties du projet afin de produire des résultats scientifiquement rigoureux et impressionnants pour Stanford.

---

## 🎯 Principes de collecte

### Standards de qualité
- ✅ Minimum 3 essais par condition
- ✅ Protocole reproductible et documenté
- ✅ Conditions contrôlées (température, surface, batterie)
- ✅ Unités SI (cm, s, rad/s)
- ✅ Incertitudes mesurées et rapportées

### Outils de mesure
- Ruban à mesurer (précision: ±0.5 cm)
- Chronomètre digital (précision: ±0.01 s)
- Multimètre (voltage, courant)
- Caméra (analyse vidéo si nécessaire)
- Marqueurs au sol (ruban coloré)

---

## 📋 PARTIE 1: Montage et Contrôle Moteur

### Expérience 1.1: Relation PWM-Vitesse

**Question**: Quelle est la relation entre le PWM et la vitesse réelle?

**Variables**:
- Indépendante: PWM (50, 100, 150, 200, 255)
- Dépendante: Vitesse (cm/s)
- Contrôlées: Batterie (7.4V ±0.2V), surface (carrelage plat)

**Protocole**:
1. Charger batterie complètement (8.4V)
2. Placer robot sur ligne de départ
3. Démarrer chronomètre et robot simultanément
4. Arrêter après exactement 3.00 secondes
5. Mesurer distance en ligne droite
6. Répéter 3 fois par valeur PWM

**Tableau de données**:
```
| PWM | Tension bat. | Essai 1 | Essai 2 | Essai 3 | Moyenne | Écart-type | Vitesse |
|-----|--------------|---------|---------|---------|---------|------------|---------|
| 50  | 8.2V         |         |         |         |         |            |         |
| 100 | 8.2V         |         |         |         |         |            |         |
| 150 | 8.1V         |         |         |         |         |            |         |
| 200 | 8.1V         |         |         |         |         |            |         |
| 255 | 8.0V         |         |         |         |         |            |         |
```

**Calculs**:
- Vitesse moyenne = Distance moyenne / 3.00 s
- Écart-type = √(Σ(xi - x̄)² / n)
- Coefficient de variation = (écart-type / moyenne) × 100%

**Graphique à produire**:
- Axe X: PWM (0-255)
- Axe Y: Vitesse (cm/s)
- Points avec barres d'erreur (±1 écart-type)
- Ligne de tendance avec équation
- R² affiché

---

### Expérience 1.2: Consommation de courant

**Question**: Comment la consommation varie-t-elle avec le PWM?

**Protocole**:
1. Insérer multimètre en série avec batterie
2. Mesurer courant pour chaque PWM (robot en mouvement)
3. Noter PWM, courant (mA), temps de fonctionnement

**Tableau**:
```
| PWM | Courant (mA) | Puissance (W) | Autonomie estimée (min) |
|-----|--------------|---------------|-------------------------|
| 100 |              |               |                         |
| 150 |              |               |                         |
| 200 |              |               |                         |
| 255 |              |               |                         |
```

**Calculs**:
- Puissance = Tension × Courant / 1000
- Autonomie = (Capacité batterie / Courant) × 60

---

## 📋 PARTIE 2: Calibration Encodeurs

### Expérience 2.1: Précision trajectoire sans calibration

**Question**: Quelle est l'erreur de trajectoire AVANT calibration?

**Protocole**:
1. Tracer une ligne droite de 200 cm au sol
2. Placer robot au début, aligné avec la ligne
3. Commander: avancer PWM=150 pendant 5 secondes
4. Mesurer déviation latérale à 50, 100, 150, 200 cm
5. Répéter 5 fois

**Tableau**:
```
| Essai | Dév. 50cm | Dév. 100cm | Dév. 150cm | Dév. 200cm | Dév. finale |
|-------|-----------|------------|------------|------------|-------------|
| 1     |           |            |            |            |             |
| 2     |           |            |            |            |             |
| 3     |           |            |            |            |             |
| 4     |           |            |            |            |             |
| 5     |           |            |            |            |             |
| Moy.  |           |            |            |            |             |
```

---

### Expérience 2.2: Précision trajectoire AVEC calibration

**Protocole**: Identique à 2.1, mais avec PID activé

**Comparaison**:
```
| Distance | Sans calib. | Avec calib. | Amélioration (%) |
|----------|-------------|-------------|------------------|
| 50 cm    |             |             |                  |
| 100 cm   |             |             |                  |
| 150 cm   |             |             |                  |
| 200 cm   |             |             |                  |
```

**Calcul amélioration**: ((Avant - Après) / Avant) × 100%

---

### Expérience 2.3: Synchronisation moteurs

**Question**: Les encodeurs permettent-ils de synchroniser les vitesses?

**Protocole**:
1. Brancher oscilloscope sur signaux encodeurs
2. Commander vitesse identique (150 PWM)
3. Mesurer fréquence des impulsions pour chaque moteur
4. Calculer différence de vitesse (%)

**Tableau**:
```
| Test | Freq. G (Hz) | Freq. D (Hz) | Diff (%) | Ajustement PWM |
|------|--------------|--------------|----------|----------------|
| 1    |              |              |          |                |
| 2    |              |              |          |                |
```

---

## 📋 PARTIE 3: Contrôle Xbox (I2C)

### Expérience 3.1: Latence commande-réponse

**Question**: Quel est le délai entre commande et action?

**Protocole**:
1. Modifier code pour envoyer timestamp via Serial
2. Appuyer sur bouton Xbox → Noter t1
3. Lire Serial Monitor → Noter t2 (réception Arduino)
4. Observer mouvement → Noter t3 (moteur démarre)
5. Répéter 20 fois

**Tableau**:
```
| Test | t1 (ms) | t2 (ms) | t3 (ms) | Latence comm. | Latence totale |
|------|---------|---------|---------|---------------|----------------|
| 1    |         |         |         | t2-t1         | t3-t1          |
| ...  |         |         |         |               |                |
| 20   |         |         |         |               |                |
| Moy. |         |         |         |               |                |
```

**Graphique**: Histogramme des latences

---

### Expérience 3.2: Fiabilité I2C

**Question**: Combien de paquets sont perdus?

**Protocole**:
1. Envoyer 100 commandes via Xbox
2. Compter commandes reçues par Arduino (via Serial)
3. Calculer taux de perte

**Résultat**:
```
Commandes envoyées: 100
Commandes reçues: ___
Taux de succès: ____%
Taux de perte: ____%
```

---

## 📋 PARTIE 4: Suivi de Ligne

### Expérience 4.1: Vitesse vs Stabilité

**Question**: Comment la vitesse affecte-t-elle le suivi?

**Protocole**:
1. Tracer circuit ovale (3m périmètre)
2. Pour vitesses: 50, 100, 150, 200 cm/s:
   - Mesurer nb de sorties de ligne
   - Mesurer temps pour tour complet
   - Calculer erreur latérale moyenne

**Tableau**:
```
| Vitesse | Tours réussis/10 | Sorties ligne | Temps tour (s) | Erreur lat. (cm) |
|---------|------------------|---------------|----------------|------------------|
| 50      |                  |               |                |                  |
| 100     |                  |               |                |                  |
| 150     |                  |               |                |                  |
| 200     |                  |               |                |                  |
```

**Graphique**: Vitesse vs Taux de réussite

---

### Expérience 4.2: Performance PID

**Question**: Quels paramètres PID donnent le meilleur suivi?

**Protocole**:
1. Tester combinaisons Kp, Ki, Kd
2. Mesurer erreur quadratique moyenne

**Tableau**:
```
| Kp   | Ki   | Kd   | Erreur RMS | Oscillations | Temps 1 tour |
|------|------|------|------------|--------------|--------------|
| 1.0  | 0    | 0    |            |              |              |
| 2.0  | 0    | 0    |            |              |              |
| 1.5  | 0.1  | 0    |            |              |              |
| 1.5  | 0.1  | 0.5  |            |              |              |
```

---

## 📋 PARTIE 5: Évitement d'Obstacles

### Expérience 5.1: Distance seuil optimale

**Question**: Quelle distance minimise les collisions?

**Protocole**:
1. Placer 10 obstacles aléatoirement dans zone 2m×2m
2. Pour seuils: 10, 20, 30, 40, 50 cm:
   - Lancer robot 5 fois
   - Compter collisions
   - Mesurer temps de traversée

**Tableau**:
```
| Seuil (cm) | Collisions/5 | Temps moyen (s) | Efficacité |
|------------|--------------|-----------------|------------|
| 10         |              |                 |            |
| 20         |              |                 |            |
| 30         |              |                 |            |
| 40         |              |                 |            |
| 50         |              |                 |            |
```

**Calcul efficacité**: (5 - Collisions) / Temps

---

### Expérience 5.2: Précision capteur ultrason

**Question**: Quelle est la précision du HC-SR04?

**Protocole**:
1. Placer obstacle à distances connues: 10, 20, 30, 40, 50 cm
2. Mesurer 50 fois chaque distance
3. Calculer moyenne et écart-type

**Tableau**:
```
| Distance réelle | Distance mesurée | Écart-type | Erreur (%) |
|-----------------|------------------|------------|------------|
| 10.0 cm         |                  |            |            |
| 20.0 cm         |                  |            |            |
| 30.0 cm         |                  |            |            |
| 40.0 cm         |                  |            |            |
| 50.0 cm         |                  |            |            |
```

---

## 📋 PARTIE 6: Navigation Autonome A→B

### Expérience 6.1: Erreur odométrique

**Question**: Comment l'erreur s'accumule-t-elle?

**Protocole**:
1. Placer repères tous les 50 cm jusqu'à 300 cm
2. Commander robot vers chaque point
3. Mesurer position réelle vs estimée

**Tableau**:
```
| Cible (cm) | Position estimée | Position réelle | Erreur (cm) | Erreur (%) |
|------------|------------------|-----------------|-------------|------------|
| 50         |                  |                 |             |            |
| 100        |                  |                 |             |            |
| 150        |                  |                 |             |            |
| 200        |                  |                 |             |            |
| 250        |                  |                 |             |            |
| 300        |                  |                 |             |            |
```

**Graphique**: Distance vs Erreur cumulée

---

### Expérience 6.2: Précision rotation

**Question**: Quelle est la précision des rotations?

**Protocole**:
1. Marquer orientation initiale au sol
2. Commander rotations: 45°, 90°, 180°, 270°, 360°
3. Mesurer angle réel avec rapporteur
4. Répéter 10 fois chaque angle

**Tableau**:
```
| Angle cible | Angle moyen mesuré | Écart-type | Erreur (°) |
|-------------|--------------------|-----------|---------   |
| 45°         |                    |           |            |
| 90°         |                    |           |            |
| 180°        |                    |           |            |
| 270°        |                    |           |            |
| 360°        |                    |           |            |
```

---

## 📋 PARTIE 7: Bras Robotique

### Expérience 7.1: Taux de réussite préhension

**Question**: Quel pourcentage d'objets sont saisis avec succès?

**Protocole**:
1. Placer 10 objets identiques (cubes 3cm)
2. Tenter saisie sur chacun (5 répétitions = 50 tentatives)
3. Noter: réussite complète / saisie partielle / échec

**Tableau**:
```
| Objet | Réussite | Partielle | Échec | Taux (%) |
|-------|----------|-----------|-------|----------|
| 1     | x/5      | x/5       | x/5   |          |
| ...   |          |           |       |          |
| 10    |          |           |       |          |
| TOTAL | /50      | /50       | /50   |          |
```

---

### Expérience 7.2: Précision positionnement

**Question**: Quelle est la répétabilité du bras?

**Protocole**:
1. Commander position cible (x=10cm, y=15cm, z=5cm)
2. Mesurer position réelle 20 fois
3. Calculer écart-type pour x, y, z

**Résultats**:
```
Position cible: (10.0, 15.0, 5.0) cm
Moyenne mesurée: (____, ____, ____) cm
Écart-type: (σx=____, σy=____, σz=____) cm
Précision globale: ±____ cm
```

---

## 📋 PARTIE 8: Intégration Finale

### Expérience 8.1: Taux de réussite mission complète

**Question**: Le système Pick & Place est-il fiable?

**Protocole**:
1. Définir mission standard:
   - Point A: (0, 0)
   - Objet à (50, 50)
   - Point B: (100, 0)
2. Lancer 30 missions complètes
3. Noter chaque étape réussie/échouée

**Tableau**:
```
| Mission | Navigation A→Objet | Saisie | Navigation Objet→B | Dépose | Succès total |
|---------|--------------------|-   -----|--------------------|--------|--------------|
| 1       | ✓/✗                | ✓/✗    | ✓/✗                | ✓/✗    | ✓/✗          |
| ...     |                    |        |                    |        |              |
| 30      |                    |        |                    |        |              |
| Taux    | ____%              | ____% | ____%              | ____% | ____%        |
```

---

### Expérience 8.2: Robustesse scénarios

**Question**: Le système fonctionne-t-il dans conditions variées?

**Scénarios**:
1. Objet déplacé de 5 cm (10 essais)
2. Obstacle imprévu sur trajet (10 essais)
3. Surface légèrement inclinée (10 essais)
4. Batterie 50% (10 essais)

**Tableau**:
```
| Scénario              | Réussites/10 | Temps moyen | Notes |
|-----------------------|--------------|-------------|-------|
| Position nominale     |              |             |       |
| Objet déplacé +5cm    |              |             |       |
| Obstacle imprévu      |              |             |       |
| Surface inclinée 5°   |              |             |       |
| Batterie 50%          |              |             |       |
```

---

## 📈 Visualisations à produire

### Pour chaque partie:

1. **Graphiques de performance**:
   - Format: PNG haute résolution (300 dpi)
   - Axes labelés avec unités
   - Légende claire
   - Barres d'erreur

2. **Tableaux de données**:
   - Format: Excel + PDF
   - Calculs vérifiables
   - Formules visibles

3. **Photos setup expérimental**:
   - Marqueurs de distance visibles
   - Configuration claire
   - Éclairage adéquat

---

## 🎯 Checklist avant collecte

Pour chaque expérience:
- [ ] Protocole écrit et relu
- [ ] Matériel de mesure calibré
- [ ] Conditions environnementales notées (T°, humidité)
- [ ] Batterie chargée (voltage vérifié)
- [ ] Tableau de données prêt
- [ ] Caméra/photos prêtes
- [ ] Code de test fonctionnel

---

## 💾 Sauvegarde des données

**Organisation fichiers**:
```
Projet_Robot_Data/
├── Partie_1_Moteurs/
│   ├── PWM_Vitesse_raw.xlsx
│   ├── PWM_Vitesse_graph.png
│   ├── Consommation_data.xlsx
│   └── Photos/
├── Partie_2_Encodeurs/
│   ├── Calibration_before.xlsx
│   ├── Calibration_after.xlsx
│   ├── Comparaison_graph.png
│   └── Videos/
...
└── README.md
```

**Backup**: Google Drive + Clé USB + GitHub

---

**Ce plan vous permet de collecter des données scientifiquement rigoureuses qui impressionneront Stanford!**

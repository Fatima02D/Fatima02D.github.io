# 🤖 Robot Mobile Autonome — Pick & Place

**Auteure :** Saida Fatimatou Zahraa Diouf  
**Programme :** Génie Mécatronique — UQTR  
**Période :** 2026  

---

## 🌍 Pourquoi ce projet ?

Ce projet est ma façon d'apprendre la robotique en construisant quelque chose de concret — un robot capable de se déplacer, de se repérer dans l'espace, et de ramasser un objet pour le déposer ailleurs.

C'est un premier pas. 


## 🎯 Objectif du projet

Construire un robot à chenilles capable de :

1. **Se déplacer** de façon hybride: autonome et contrôlée (téléopération via manette Xbox)
2. **Se repérer** dans l'espace (odométrie + capteurs)
3. **Détecter** un objet (vision par caméra)
4. **Ramasser** cet objet (bras robotique)
5. **Le déposer** à un point B défini (navigation autonome)

---

## 🛠️ Hardware utilisé

| Composant | Rôle |
|---|---|
| Châssis Hiwonder à chenilles | Locomotion tout-terrain |
| Raspberry Pi 4B 4GB | Cerveau central + ROS2 |
| ESP32 TTGO T-Display | Communication Bluetooth + écran |
| STM32 | Contrôle bras robotique (phase 2) |
| Hiwonder Encoder Motor Module | Driver moteurs + encodeurs |
| HC-SR04 | Détection d'obstacles |
| LiPo 7.4V 2200mAh | Alimentation moteurs |
| Manette Xbox | Téléopération |
| Caméra RPi (phase 2) | Vision + détection balle |
| Bras 5DOF (phase 2) | Manipulation |

---

## 🗺️ Feuille de route

```
Phase 1 — Base hardware .............. ✅ EN COURS
Phase 2 — Téléopération Xbox ......... ⏳ Prochaine
Phase 3 — Odométrie + localisation ... 📅 Planifiée
Phase 4 — Évitement d'obstacles ...... 📅 Planifiée
Phase 5 — Navigation autonome A→B .... 📅 Planifiée
Phase 6 — Vision (détection balle) ... 📅 Planifiée
Phase 7 — Bras robotique ............. 📅 Planifiée
Phase 8 — Pick & Place complet ....... 📅 Finale
```

---

## ⚙️ Architecture système

```
Xbox Controller (Bluetooth)
        ↓
      ESP32          ← communication + écran TFT
        ↓ UART
   Raspberry Pi 4    ← cerveau central + ROS2
        ↓ I2C
  Hiwonder Module    ← moteurs + encodeurs
        ↓
  Chenilles gauche / droite
```

---

## 📁 Structure du repo

```
mobile-manipulator-robot/
├── README.md
├── docs/
│   ├── logbook.md        ← journal de bord
│   ├── hardware.md       ← branchements + inventaire
│   └── decisions.md      ← choix techniques justifiés
├── firmware/
│   ├── esp32/
│   └── stm32/
├── ros2_ws/              ← phase 2+
├── vision/               ← phase 6+
└── media/
    └── photos/
```

---

## 📓 Journal de bord

Chaque session est documentée dans [`docs/logbook.md`](docs/logbook.md).

Format :
```
## YYYY-MM-DD
Objectif :
Accompli :
Problèmes :
Solution :
Prochaine étape :
```

---

## 🔗 Contact

**Portfolio :** [fatima02d.github.io](https://fatima02d.github.io)  
**GitHub :** [github.com/fatima02d](https://github.com/fatima02d)  
**LinkedIn :** [Saida Fatimatou Zahraa Diouf](https://www.linkedin.com/in/saida-fatimatou-zahraa-diouf)

---

*

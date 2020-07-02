# Projet PAF mini-os
## Informations
Ce projet a été réalisé en projet de fin de première année (PAF) à Télécom Paris.

Le projet était encadré par Guillaume Duc.

## Projet
Le principe du projet est d'écrire un OS (minimal) sur un Luminary Micro Stellaris LM3S6965EVB équipé d'un processeur ARM Cortex-M3.

## Dépendances
Le projet utilise Qemu pour se lancer. Au début du projet il s'agissait de la version QEMU System ARM officielle. Une fois le système de fichier commencé, une version modifiée de QEMU a été utilisée, une zone de RAM a été ajoutée entre les adresses `0xF0000000` et `0xF0A00000`. Il faut pour cela modifier le fichier `hw/arm/stellaris.c`, puis recompiler QEMU et le réinstaller.

La chaîne GCC pour arm-none-eabi est utilisée pour compiler et déboguer le projet.

## État final
A la fin du projet le changement de contexte et la gestion des processus fonctionnaient.

Les appels système ont l'air de fonctionner plutot bien dans la globalité mais aucun test intensif n'a été réalisé. L'appel système fork ne fonctionne pas.

Le système de fichier n'a presque pas été testé et est donc probablement rempli de bugs, mais le peu que j'ai essayé ne fonctionnait pas trop mal.

Les processus sont en permanence avec des privilèges élevés.

Rien n'a été optimisé globalement, l'efficacité de fonctionnement n'étant pas l'objectif.

## Source
### Liens originaux
`https://perso.telecom-paristech.fr/duc/cours/paf/mini-os/mini-os-1.html`
`https://perso.telecom-paristech.fr/duc/cours/paf/mini-os/mini-os-2.html`
`https://perso.telecom-paristech.fr/duc/cours/paf/mini-os/mini-os-3.html`
`https://perso.telecom-paristech.fr/duc/cours/paf/mini-os/mini-os-4.html`

### Copie
Les pages ci-dessus ont été sauvegardées à la fin du projet et leur contenu est dans le dossier `source`.

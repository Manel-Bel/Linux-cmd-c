# Linux-cmd-c
Recreation des commande de linux (mkdir , ls, touch, rm, ..) avec une lecture de fichier 

pour execution du programme , fait taper la commande 
    1. make 
    Sur le terminal suivi après du nom de l'exécutable avec le nom de fichier de votre choix 
        2. ./my_program (nom_de_votre_fichier)


## Description :
Le projet "jsh" est un interpréteur de commandes interactif, conçu pour offrir des fonctionnalités similaires aux shells classiques comme Bash. Ce shell permet l'exécution de commandes externes, la gestion des redirections et des tubes, et intègre des commandes internes. Il prend également en charge la gestion des tâches (job control), permettant aux utilisateurs de manipuler des groupes de processus.

## Fonctionnalités Principales :

Gestion des Tâches : Création et gestion de groupes de processus avec possibilité de basculer entre l'avant-plan et l'arrière-plan.
Commandes Internes : cd, pwd, ?, exit, jobs, kill.
Redirections et Pipes : Support pour la redirection des flux standard et les pipes.
Multithreading et Processus : Utilisation de threads pour la gestion des processus et la surveillance des descripteurs de fichiers.
Automatisation des Tests : Utilisation de Robot Framework et Jenkins pour l'automatisation des tests, avec scripts en Python et Bash.

## Technologies Utilisées :
Langages : C, Bash
Environnements : Linux (Debian/Ubuntu)

## Installation et Utilisation :

Clonez le dépôt : git clone <URL-du-dépôt>
Compilez le projet : make
suivi après du nom de l'exécutable avec le nom de fichier de votre choix 
Lancez le shell : ./my_program (nom_de_votre_fichier)

penser à utiliser  : make clean 
    dans le terminal si tout changement est effectué


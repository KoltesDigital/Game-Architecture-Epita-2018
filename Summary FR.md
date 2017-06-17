# Récapitalif du cours

> Résumé des enseignements principaux vus à travers le cours.

Même si le cours prend pour exemple un moteur de jeu, ces enseignements peuvent être appliqués dans d'autres domaines.

## Pourquoi s'intéresser à l'architecture ?

* Utile sur des projets de longue durée, avec de grandes équipes.
* Permet une meilleure maintenabilité et évolution de la base de code.
* Permet de réutiliser des modules dans d'autres projets.
* Peut permettre de réduire le nombre de bugs.

## Modularité hiérarchique

Lorsque les projets gagnent en complexité, le code peut être partager en plusieurs modules. Ils peuvent être organisés hiérarchiquement, du bas niveau au haut niveau. Les modules peuvent accéder aux modules inférieurs, mais n'ont pas le droit d'accéder aux modules supérieurs.

Voici des exemples de modules dans un moteur de jeu, allant du haut niveau au bas niveau :

* editeur, outils ;
* sous-systèmes spécifiques au jeu ;
* systèmes de gameplay ;
* sous-systèmes : rendu, physique, réseau... ;
* données (resources / assets) ;
* fonctionnalités de base : debug, système de fichiier, math, string... ;
* abstraction de la plateforme.

## Dépendances

Les modules de haut niveau dépendent des modules de plus bas niveau.

Par exemple, un système gameplay nécessite sûrement des fonctions mathématiques. Il y a une dépendance forte du gameplay envers la bibliothèque mathématique.

Dans certains cas, il est utile de dépendre uniquement d'un ensemble de fonctionnalités, mais pas de leur implémentation concrète. Une interface permet de déclarer qu'un objet possède des fonctionnalités, sans spécifiquer comment il les réalise.

Par exemple, le moteur de rendu dépend d'un système de fenêtre, typiquement fourni par le système d'exploitation ou par une bibliothèque système. Afin de rendre le jeu cross-platform, une interface devrait abstraire le système de fênetre. Pour que le jeu puisse fonctionner sur une plateforme, il faudra alors implémenter cette interface pour la-dite plateforme.

Quand un module A a une dépendance sur B, et B sur A, c'est un cycle de dépendance. Cela devrait être évité, car il contraint les deux (ou plus) modules : l'un ne peut pas être réutilisé sans les autres, et si l'un change, les autres peuvent devoir être changés avec.

Pour casser un cycle de dépendance, regardez si vous nécessitez une dépendance vers l'implémentation. Souvent, on ne nécessite qu'une dépendance vers des fonctionnalités, mais pas vers la façon concrète dont elles sont implémentées. Dans ce cas, vous pouvez abstraire ces fonctionnalités avec une interface.

Attention au design pattern Singleton, qui crée très facilement des cycles de dépendance.

L'injection de dépendance est un terme global décrivant la mise en relation des modules. Le principe d'inversion de dépendance fait référence à l'ensemble de règles qui indiquent que les modules doivent se fonder sur des abstractions, c'est-à-dire que la mise en relation est faite au moyen d'intrerfaces.

## Encapsulation

Quand vous utilisez une classe, vous ne devriez pas savoir comment elle fonctionne. Vous ne devriez connaître que les fonctionnalités qu'elle propose.

Une mauvaise encapsulation des classes peut avoir pour conséquence :

* porter trop de responsabilités ;
* avoir trop de dépendances ;
* être plus difficile à tester.

## Principe de responsabilité unique

Ne soyez pas avare de classes ! Chaque classe ne devrait avoir qu'une seule responsabilité. Si une classe doit gérer plusieurs responsabilités,

* l'implémentation va être plus volumineuse, et pourrait donc contenir plus de bugs ;
* elle sera plus dure à tester. Et parce qu'elle peut contenir plus de bugs, ça devient très dangereux !
* de nouvelles fonctionnalités seront plus dure à rajouter ;
* réutiliser la classe implique de réutiliser toutes les responsabilités d'emblée.

## RAII

Une resource qui peut être acquise et libérée peut être représentée par une classe, dont le constructeur acquiert la resource et le destructeur la libère.

Par exemple :

* l'accès à un fichier est typiquement représenté par une classe `File`, qui ferme le handle automatiquement à la destruction ;
* `std::lock_guard` automatiquement verrouille et déverrouille un mutex ;
* `std::unique_ptr` libère automatiquement un pointeur.

## Appartenance de la mémoire

Le propriétaire de la mémoire est responsable de la durée de vie des variables, c'est-à-dire de leur allocation et libération.

Dans le cas d'une variable simple, le propriétaire est la portée (_scope_) de sa définition. D'un point de vue bas niveau, la variable vit dans la pile (_stack_), et sortir du _scope_ libère l'espace pile correspondant. Par exemple :

	void function()
	{
		Object o;
		o.doSomething();
		...
	} // o est détruit ici.

Dans le cas d'un pointeur, a bloc mémoire est alloué sur le tas (_heap_), et le pointeur n'est que l'adresse de ce bloc. Il est très important que le propriétaire soit clairement identifé :

* si le bloc mémoire n'est pas libéré, il y a des fuites mémoire (_memory leaks_) et le programme consomme trop de mémoire ;
* si le bloc mémoire est libéré deux foix, la deuxième fois n'est pas légale et déclenche une erreur.

De plus, l'ordre des allocations et libérations est importante.

## Handle

Parfois, nous voulons cacher des objets, par exemple pour garder le contrôle et l'appartenance, mais d'autres systèmes doivent pouvoir les manipuler. Pour ce faire, on donne à ces systèmes un moyen de se référer à ces objets, sans jamais y accéder. Par exemple :

* un _file handle_ est retourné lorsque le système d'exploitation ouvre un fichier. Il est nécessaire pour effectuer toute opération sur le fichier, en particulier pour lire et écrire.
* un _token_ est généré lorsque quelqu'un se connecte à son compte sur un site web. Grpace à un cookie, ce token est envoyé au serveur à chaque requête.

## Spécialisation

Parfois, nous avons besoin de spécialiser un comportement. Dans les languages modernes orientés objet, il y a habituellement deux façons de le faire.

L'héritage est un type de spécialisation où l'on augmente des fonctionnalités existantes.

Les interfaces peuvent être vues comme un cas spécial d'héritage, où les fonctionnalités sont spécifiées mais pas implémentées.

La composition est un autre moyen de spécialiser un comportement. Faire une fonction qui dépend d'un autre fonction peut être vu comme une spécialisation.

Le pattern Entité-Composant rend générique la composition. L'entité n'est qu'un simple conteneur, avec des composants. Ceux-ci peuvent être vus comme des compétences, donc en ajoutant un composant, l'objet gagne de nouvelles compétences. Cet idiome est surtout utilisé pour gérer la composition au _runtime_.

Le pattern Stratégie combine les principes de composition et d'injection de dépendance, où l'objet hôte se fonde sur un autre objet pour faire les traitements.

D'un point de vue de la mémoire, l'héritage et la composition sont essentiellement identiques.

## Le pattern Visiteur

Le pattern Visiteur permet de découpler les données du code qui les traite.

* Les données ne font que déclarer les valeurs à une interface visiteur
* Le visiteur concret (implémentation de l'interface) traite les données.

Ce pattern est utile pour déconstruire un modèle d'héritage sans nécessiter de _dynamic casts_.

	interface FSVisitor
		handleFile(FileInfo &)
		handleDirectory(DirectoryInfo &)

	abstract class FSEntry

	class FileEntry : FSEntry
		FileInfo info
		accept(FSVisitor &visitor) => visitor.handleFile(info)

	class DirectoryEntry : FSEntry
		DirectoryInfo info
		accept(FSVisitor &visitor) => visitor.handleDirectory(info)

	class Search : FSVisitor
		handleFile(FileInfo &) ...
		handleDirectory(DirectoryInfo &) ...

## Modèle Vue Contrôleur (MVC)

L'idiome MVC permet de découpler les données (modèle) de sa représentation (vue). La vue ne pas pas changer le modèle directement : les actions de modifiication passent par un contrôleur, qui s'occupe de changer le modèle. Ensuite, le modèle signale à la vue ses changements.

D'autres variations ont des différences subtiles (MVD, MVVM, MVP...). Cependant, le principe de base reste qu'un modèle est indépendant de la vue. Typiquement,

* le modèle est bas niveau, car il ne contient que des données et les comportements associés ;
* la vue est haut n iveau, car elle nécessite un rendu d'interface graphique ;
* le contrôleur est entre les deux, car il est executé par la vue, gère le modèle, et peut nécessiter d'autres sous-systèmes.

Il est alors possibles d'avoir plusieurs vues pour le même modèle. Dans ce cas, il peut y avoir un ou plusieurs contrôleurs, en fonction du paradigme modèle-view et de si les vues sont significativement différentes.

## Tests unitaires

Les tests unitaires sont en fait une méthodologie de programmation, où l'on commence par écrire les spécifications de ses futures modules. Il se trouve que les spécifications sont executables, donc on peut s'assurer que les spécifications sont bien remplies. Ainsi, cette façon de programmer est bien plus profonde que d'écrire des tests après avoir implémenté des fonctions.

Dans tous les cas, les tests sont un filet de sûreté essentiel. Si une régression apparaît, les tests se doivent de le montrer.

Le mieux est d'automatiser les tests. Par exemple, vous pouvez les lancer à chaque _commit_ sur le _repository_. Cela aidera à réparer les régressions dès qu'elles apparaîssent.

## Métriques

Les métriques sont des indicateurs de la santé du code. Quelques exemples :

### Par projet

* _Code coverage_ ;
* Nombre de lignes dupliquées, ou taux de duplication ;
* Nombre de bugs, par ligne de code, ou dans le temps.
* Nombre de dépendances externes.

### Par fichier / classe

* Nombre de lignes ;
* Nombre de fonctions ;
* Profondeur d'héritage.

### Par fonction

* Complexité cyclomatiques ;
* Nombre de parameters : quand un appel a plusieurs paramètres, il peut être dur de savoir qui fait quoi ;
* Nombre de lignes.

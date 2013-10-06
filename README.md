bbstrassenfest
==============

Musterlösung für Berliner und Brandenburger Volks- und Strassenfeste 2013 aus
dem LinuxMagazin 11/13

Abhängigkeiten
--------------

Da diese Musterlösung auf Tntnet basiert, muss Tntnet und Cxxtools installiert
sein. Da es sehr neue Features von Tntnet nutzt, wird momentan Tntnet aus git
benötigt. Die aktuellen stabilen Versionen cxxtools-2.2 und tntnet-2.2 genügen
nicht.

Compilieren und Ausführen
-------------------------

Das Projekt verwendet die autotools als build system. Wird ein Autotools
basiertes Projekt aus einem Distributionspaket gebaut, steht ein configure
Skript zur Verfügung. Da dieses ein generiertes Skript ist, wird es in git nicht
eingecheckt. Wird das Projekt also aus git ausgecheckt, muss es also zunächst
erzeugt werden.

Nach dem auschecken aus git muss zunächst das Kommando

    autoreconf -i

ausgeführt werden. Damit wird das Buildsystem initialisiert. Wir erhalten unter
anderem ein configure Skript.

Zum erstellen der Applikation wird dieses configure Skript dann im
Projektverzeichnis ausgeführt:

    ./configure

Es prüft alle Abhängigkeiten und erstellt dann ein Makefile. Mit

    make

Wird die Applikation erstellt. Zum Ausführen muss ins src-Verzeichnis gewechselt
werden. Dort kann die Applikation gestartet werden:

    cd src
    ./bbstrassenfest

Da es sich um eine Webapplikation handelt, benötigt man dann einen Browser. Der
Server läuft auf Port 8000, so dass mit einem lokalen Browser die Applikation
unter `http://localhost:8000/` abrufbar ist.

Der Port lässt sich in der Datei `bbstrassenfeset.conf` im src Verzeichnis
ändern. Dort befinden sich aus Einstellungen für das Logging.


Struktura plików gry
====================



Foldery
-------

### Główne podfoldery

```
Scripts/			; Inne skrypty.
Actions/			; Współdzielone, typowe zdarzenia, w tym akcje ciągłe.
Objects/			; Typy obiektów świata gry, np. dźwignia, drzewo - zestawy grafik, animacji.
Actors/				; Typy aktorów - bardziej stworzenia, np. postacie, potwory - zestawy -||-.
Maps/				; Mapy, w tym listy obiektów, wyzwalaczy i zdarzeń map, konfiguracja.
Sounds/				; Jednorazowe dźwięki, dość uniwersalne - odtwarzane z naciskiem na buforowanie.
Musics/				; Powtarzające się lub ciągłe muzyka, podkład - odtwarzane strumieniowo.
Dubbing/			; Dubbing dialogów - osobno, bo być tak powinno. ;)
Fonts/				; Niestandardowe czcionki, proste ikonki.
Interface/			; Elementy związane z UI, interfejsem, w tym konfiguracja.
Cutscenes/			; Scenki między lokacjami, zdarzeniami w grze itd.
Items/				; Przedmioty, grafiki, informacje, statystyki.
Shaders/			; Skrypty, maski, grafiki shaderów.
Other/				; Inne rzeczy, np. logo.
```



### Dalsze podfoldery

W folderach niemających zdefiniowanej dalszej struktury - np. `Sounds`, ale też `Maps/<FolderMapy>` - można używać kolejnych folderów, np. `Sounds/Magic`, czy też `Maps/<FolderMapy>/back`.



Pliki
-----

### Nazwenictwo plików

* W strukturze plików poniżej są zawarte także rozszerzenia - to tylko dla rozróżnienia typu danych (czy dźwiękowy, graficzny czy czystej informacji).

* Dany plik/zasób może być przekierowaniem do innego zasobu - wtedy jako rozszerzenie powinnien użyć `lnk` oraz w treści powinien mieć jedynie nazwę/id/ścieżkę zasobu na jaki wskazuje.

* Standardowo obowiązkowe elementy są zaznaczone z wykrzyknikiem (`!`) z początku komentarza struktury. Elementy z pytajnikiem (`?`) - bardzo niepewne.

* Oprócz plików ze struktury mogą istnieć także inne pliki - np. przy grafikach powinien być plik projektu do utworzenia danego zasobu. Nie będą one używane przez silnik, ale warto uwspólnić takie dane, np. do późniejszej łatwej edycji.

* Inne informacje, np. przeznaczenie pliku, są w formie komentarza (`; `) na strukturze poniżej.

* Format plików konfiguracyjnych, list obiektów to JSON, struktura kolejnych została opisana także tutaj.

* Format plików skryptowych, wyzwalaczy, zdarzeń, akcji to LUA, zostały one opisane w `Scripts.md`.



### Struktura plików

Folder - z `/`, plik bez. Dla opisu informacji zawartych w plikach konfiguracyjnych użyto `-` jako wskazanie na pole lub podelement. Od `; ` - komentarz.

```
Objects/*
	LeverBehindInARoom/
		skeleton.json			; Informacje o animacji szkieletowej.
		texture.json			; Informacje o teksturach dla animacji (szkieletowej wg. schematu z DB lub dla sprite:
			- states {} 		; ! Tablica stanów, klucze np. `moving_left`, `idle`...
				- frames		; ! Liczba klatek dla animacji
				- timestamps []	; Różnice w czasie dla kolejnych klatek, lub jedna wartość
								; 	jak wspólna różnica w czasie dla kolejnych klatek.
				- mode			; ? Tryb animowania:
								;	0, 'static' lub brak - klatka odrazu jest nakładana,
								; 	1, 'linear' - przenikanie, liniowe zmienianie przeźroczystości,
								;	2, 'ease-all' - przenikanie stępione, wolny start, koniec,
								;	3, 'ease-in' - przenikanie stępione z początku, wolny start,
								;	4, 'ease-out' - przenikanie stępione z końca, wolny koniec,
								;   lub tablica - wartości przeźroczystości dla przejścia Beziera.
		texture.png				; Tekstury (szkieletowa), klatki aniamcji (sprite) lub tekstura (statyczna).
								; Jeśli brak, obiekt nie ma reprezentacji wizualnej.
		object.json				;
			- lx				; ? Długości w odpowiednich osiach obiektu - wymusza odpowiednie rozmiary.
			- ly				; ? -||-
			- ox				; Punkt/pozycja pochodzenia - Wskzany punkt jest miejscem względem
			- oy				;   animacji, od którego jest uznawany środek obiektu dla dla gry.
								;	Jesli nie określone oXYZ - używane są środkowe z wymiarów  elementu.
			- cx				; Szerokość kolizji. Jeśli tryb koła - promień koła od środka.
			- cy				; Wysokość kolizji. Jeśli zero lub nieokreślony - tryb koła.

Actors/*						; Każdy `Actor` to także `Object`, więc elementy dziedziczone.
	Guard03/
		config.json				; ! Informacje o postaci.
			- name				; ! Nazwa własna, wyświetlana.
			; informacje zależne od mechanik - @todo do ustalenia itd., btw czy to wgle tutaj czy tylko w Maps?
			- tags				; Lista tagów postaci, np. `good,old,mage`.
			- description		; Opis postaci w dzienniku.
			- health
			- mana
			- attack
			; i inne informacje...

Maps/
	South Castle Tower Floor 1/
		background.json 		; Definiuje pozycje, typy obiektów w tle mapy.
			- elements [{}]
				- id			; Nazwa/ID, używane do połączenia danego obiektu z wyzwalaczami i zdarzeniami.
				- type			; ! Nazwa typu odpowiedniego obiektu, np. `Mill01`.
				- x				; ! Początkowa pozycja
				- y				; ! x - lewo/prawo, y - w głąb (definiuje warstwe paralaksy, z - wysokość
				- z				; ! ...
				- angle			; Początkowy obrót obiektu (i jego grafik/animacji).
				- state			; Początkowy stan animacji
				- time			; Początkowy czas animacji
				- action		; Przypisana akcja, typowe zachowanie.
		objects.json			; Definiuje pozycje, typ obiektu/aktora na mapie.
								;	Może zawierać inne informacje do nadpisania (np. HP).
			- objects [{}]
				- id			; Nazwa/ID, używane do połączenia danego obiektu z wyzwalaczami i zdarzeniami.
				- type			; ! Nazwa typu odpowiedniego obiektu, np. `Guard03`.
				- x				; ! Początkowa pozycja
				- y				; ! x - lewo/prawo, y - w głąb, z - wysokość
				- z				; ! ...
				- angle			; Początkowy obrót obiektu (i jego grafik/animacji).
				- state			; Początkowy stan animacji
				- time			; Początkowy czas animacji
				- action		; Przypisana akcja, typowe zachowanie.
				; i inne niestandardowe informacje, np. dot. postaci (np. jakieś statystyki).
		scripts.lua				; Definiuje wyzwalacze i wydarzenia na mapie.
			@info Omówiony w innym pliku (`Scripts.md`)
		config.json				; ! Konfiguracja mapy
			- name				; ! Nazwa wyświetlana
			; i inne informacje, np.
			- music.list []		; Lista nazw standardowej muzyki w tle.
			- music.random		; Flaga, czy losowe utwory (standardowo tak).

Sounds/							; Jednorazowe dźwięki, dość uniwersalne - odtwarzane z naciskiem na buforowanie.
	Some Sound Name.ogg			; @todo Struktura do omówienia.

Musics/							; Powtarzające się lub ciągłe muzyka, podkład - odtwarzane strumieniowo.
	Example Background.ogg		; Pliki nie muszą, ale oczywiście mogą być w folderach.

Dubbing/						; Dubbing dialogów - osobno, bo być tak powinno. ;) PS: bez "dubbingu" obiektów, np. drzew :P
	Act 1/						; 	Dubbing będzie podzielony na: Akty, Zadania, Lokacja, Sceny (plik), Kwestie (po offsetach).
		Anvil Delivery/			; 	Poza Aktami będą także: `Common` - wspólne dla postaci, grup, odgłosów ludzkich z dialogami,
			Saint Egg Villge/	; 	`Actors` - dla specyficznych postaci (z podziałem na pliki kwestii) i `Other` - dla innych.
				FirstMeeting.ogg	; ! Plik dźwiękowy z kolejnymi nagraniami, kwestiami w miare unikatowymi dla tego dialogu.
				FirstMeeting.json	; ! Plik z ustawieniami, offsetami tych kwestii i inne.

Fonts/
	Consolas.ftf

Interface/
	IngameMenu/					; Każdy dodatkowy interfejs (możliwy do wywołania po nazwie) ma osobny folder.
		config.json				; ! Plik opisujący rozmieszczenie i typy elementów interfejsu oraz wywołane przez nie skrypty.
		scripts.lua				; Plik przechowujący ewentualne skrypty dla interfejsu.
		buttons/				; Powiązane treści, np. grafiki, animacje itd. także damy tutaj, niekoniecznie w folderach.
			exit.png
			exit_pressed.png

Items/							; @todo do przemyślenia
	Stick sword/
		graphic.png				; ! Podgląd w menu (może być animacją z konfiguracją `json` itd).
		config.json				; ! Konfiguracja przedmiotu
			- name				; ! Nazwa wyświetlana
			; informacje zależne od mechanik... @todo
			- tags				; Lista tagów przedmiotu, np. `warrior,sword,short,wooden`.
			- description		; Opis przedmiotu w menu.
			- durability		; Liczba pozostałych użyć.
			- health			; Odnawiane punkty życia.
			- mana				; Odnawiane punkty many.
			- attack			; Zadawane obrażenia.
			; i inne informacje...

Other/
	Logo: SzczurEngine.png
	Logo: Hajsownicy.f3.r1.png  ; Animacje także tutaj możliwe.
	Logo: Gimper.png
	HUD.png
```

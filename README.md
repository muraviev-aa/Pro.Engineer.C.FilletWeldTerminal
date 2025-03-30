<a name="readme-top"></a>

![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![CLion](https://img.shields.io/badge/CLion-black?style=for-the-badge&logo=clion&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
<p align="left">
<img src="images/gtk.png" alt="drawing" width="300"/>
</p>

# Многомодульная программа 
### Приложение "Определение минимального катета сварного шва стальных конструкций"

Цель разработки: реализация требований табл. 38 СП 16.13330.2017 изм. 2, 3.

При запуске приложения, для получения результата, необходимо ввести следующие параметры:

* толщина первого привариваемого элемента;
* толщина второго привариваемого элемента.

<strong> &#128194; weld_fillet_gui </strong> - настольное приложение

 Приложение разработано  с использованием **Glade ,GTK+ 3, GLib, Cairo**. 

 <p align="center">
<img src="images/weld_gui.png" alt="drawing" width="700"/>
</p>


 Предусмотрено создание **pdf** файла с результатами подбора катета.

<p align="center">
<img src="images/report.png" alt="drawing" width="690"/>
</p>

<p align="right">(<a href="#readme-top">вверх</a>)</p>

 <strong> &#128194; weld_fillet_terminal </strong> - консольное приложение


Приложение имеет текстовый интерфейс пользователя. Такая возможность, при разработке в Windows, предоставляется библиотекой управления терминалом **curses.h**.

<p align="center">
<img src="images/weld.png" alt="drawing" width="800"/>
</p>

<p align="right">(<a href="#readme-top">вверх</a>)</p>


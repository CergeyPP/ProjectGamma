Проект "ProjectGamma"

Разработка проекта началась в 2022 году, продолжается по сей день.

Проект представляет собой игровой движок. Объекты на сцене содержат компоненты, которые легко настраиваются, что позволяет менять их поведение так, как душе угодно. Объекты также могут друг от друга наследоваться, создавая сложную иерархию.
Реализованные компоненты:
- Источник света
    Может быть направленным, точечным или прожектором.
    Можно задать свой материал света.
- Компонент полигональной сетки.
    Можно использовать как простой мэш куба, так и загрузить его из файла 3D модели(например FBX, OBJ и т.д.) (появится в следующей версии).
    К компоненту подключается материал для отрисовки. В материал можно загрузить текстуру(ы) для отрисовки, а также указать тип шейдера.
- Компонент ввода.
    Получает сообщения системы ввода о нажатиях на клавиатуре или мыши, движениях мыши, прокрутке и т.д.
- Компонент камеры.
    Задает позицию и направление взгляда для рендера.
- Физические компоненты.
    RigidBody и CharacterController.
    Реализовано с помощью физического движка PhysX.
- API компонент для скриптинга.
    Наследование от ScriptableComponent позволяет написать свой скрипт и подключить его к объекту.
    
Любой из этих компонентов можно подключить к объекту, или наоборот отключить, чтобы редактировать его поведение.

Технологии, используемые в проекте:
- Язык программирования - С++
- Библиотека STL - контейнеры для хранения объектов
- Физический движок PhysX
- Библиотеки GLFW и GLEW - для отрисовки 3D графики(OpenGL)
- Шейдерный язык GLSL для шейдерных программ
- Библиотека SOIL - загрузка текстур
- Assimp - загрузка моделей


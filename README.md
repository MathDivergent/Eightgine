Структура папок движка:
.Eightgine - Содержит 3 ключевые папки.
	.Binaries - Содержит исполняемые файлы и шаред библиотеки. Исполняемый файл, сгенерированный сборкой в зависимости от опции WITH_EDITOR, будет запускать пустой проект с редактором и без него.
	.Development - Содержит файлы необходимые для разработки проекта. Содержит шаблон CMakeLists.txt файла для сборки проекта.
		.Engine - Содержит исходный код движка и редактора.
		.Game - Содержит шаблон исходного кода для сборки исполняемого файла проекта.
		.ThirdParty - Содержит исходные файлы сторонних библиотек, фреймворков, необходимых для движка и редактора.
		.Intermediate - Содержит артефакты сборки и промежуточные файлы. Может быть удалена.
	.Resources - Содержит сереализированные данные, ассеты редактора.

Структура папок проекта:
.Project - Содержит 3 ключевые папки. Может иметь произвольное имя.
	.Binaries - Содержит исполняемые файлы и шаред библиотеки. Исполняемый файл, сгенерированный сборкой в зависимости от опции WITH_EDITOR, будет запускать проект с редактором и без него.
	.Development - Содержит файлы необходимые для разработки проекта. Содержит копию шаблона CMakeLists.txt файла для сборки проекта. Может изменятся разработчиком.
		.Game - Содержит исходный код проекта. Содержи копию шаблона исходного кода для сборки исполняемого файлы проекта.
		.ThirdParty - Содержит исходные файлы сторонних библиотек, фреймворков, необходимых для проекта.
	.Resources - Содержит сереализированные данные, ассеты проекта.

Структура папок билда:
.Project - Содержит 2 ключевые папки. Может иметь произвольное имя.
	.Binaries - Содержит исполняемые файлы и шаред библиотеки.
	.Resources - Содержит сереализированные данные, ассеты проекта.

Замечания:
	.Binaries - Кастомные библиотеки, добавленные в CMakeLists.txt, будут автоматически копироваться.
	.Development - Может быть удалена для сборки с включенной опцией WITH_EDITOR.

Архитектура движка:
.Core
	.CMain
	.CTime
	.CVector
	.CObject
	.CSpace
	.CWorld
	.CLocation
	.CViewport
	.CCamera
	.CWindow
	.CTransform
	.SPosition
	.SRotation
	.SScale
	.CCollider
	.CMath
	.CResourceManager
	.CEventManager
	.CMemoryManager
	.CReflection
	.CSerialization
	.CObjectTemplate
	.CObjectSchema
	.CWorkerThread
	.CThreadTask
	.CThreadPoolManager

.Renderer - Содержит классы для работы с графикой.
	.RTexture
	.RSprite
	.RSpriteComposite
	.RRenderTarget
	.RPostProcessManager	
	.RRendererManager

.Audio - Содержит классы для работы с аудио.
	.AAudio
	.ASound
	.AMusic
	.AAudioManager

.Input - Содержит классы для обработки перефирийных событий.
	.IMouseInpit
	.IKeyboardInput
	.IJoystickInput
	.IInputManager

.Physics - Содержит классы для программирования физики.
	.PMovementPhysics
	.PDynamicPhysics
	.PCOllisionResolver

.Scripting - Содержит классы для программирования состояния, поведения, скриптов.
	.SStateMachine
	.SExecutionTree
	.SScriptableObject
	.SScriptingContext

.Objects - Содержит классы для программирования и разработки игровых обьектов.
	.CObjectComponent
	.OStaticObject
	.OKinematicObject
	.ODynamicObject

.Lighting - Содержит классы для программирования и разработки освещения.
	.LStaticLight
	.LDynamicLight
	.LShadow
	.LLightingEditor

.Animations - Содержит классы для программирования и разработки анимаций.
	.ABaseAnimation
	.ASpriteAnimation
	.ASkeletalAnimation
	.AAnimationEditor

.Particles - Содержит классы для программирования и разработки частиц.
	.PParticlesBase
	.PParticlesEditor

.Network - Содержит классы для сетевого программирования.
	.NConnectionBase
	.NServer
	.NClient
	.NRemoteProcedureCall
	.NNetworkManager

.GUI
	.GBase
	.GButton
	.GSliderBlock
	.GSliderBar
	.GCheckButton
	.GRadioButton
	.GBox
	.GLayout
	.GTextBox
	.GTextField
	.GPanel

.Editor
	.EDebugDrawUtility
	.EDetailsPanel
	.EObjectHierarchy
	.EAssetsBrowser
	.ELocationEditor
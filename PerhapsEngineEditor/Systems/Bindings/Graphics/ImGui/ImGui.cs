using System;
using System.Runtime.InteropServices;
using System.Numerics;

namespace Perhaps.Engine
{
    public enum ImGuiWindowFlags
    {
        ImGuiWindowFlags_None = 0,
        ImGuiWindowFlags_NoTitleBar = 1 << 0,   // Disable title-bar
        ImGuiWindowFlags_NoResize = 1 << 1,   // Disable user resizing with the lower-right grip
        ImGuiWindowFlags_NoMove = 1 << 2,   // Disable user moving the window
        ImGuiWindowFlags_NoScrollbar = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
        ImGuiWindowFlags_NoScrollWithMouse = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
        ImGuiWindowFlags_NoCollapse = 1 << 5,   // Disable user collapsing window by double-clicking on it. Also referred to as "window menu button" within a docking node.
        ImGuiWindowFlags_AlwaysAutoResize = 1 << 6,   // Resize every window to its content every frame
        ImGuiWindowFlags_NoBackground = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
        ImGuiWindowFlags_NoSavedSettings = 1 << 8,   // Never load/save settings in .ini file
        ImGuiWindowFlags_NoMouseInputs = 1 << 9,   // Disable catching mouse, hovering test with pass through.
        ImGuiWindowFlags_MenuBar = 1 << 10,  // Has a menu-bar
        ImGuiWindowFlags_HorizontalScrollbar = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
        ImGuiWindowFlags_NoFocusOnAppearing = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
        ImGuiWindowFlags_NoBringToFrontOnFocus = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
        ImGuiWindowFlags_AlwaysVerticalScrollbar = 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
        ImGuiWindowFlags_AlwaysHorizontalScrollbar = 1 << 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
        ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 16,  // Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows, because more convenient)
        ImGuiWindowFlags_NoNavInputs = 1 << 18,  // No gamepad/keyboard navigation within the window
        ImGuiWindowFlags_NoNavFocus = 1 << 19,  // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
        ImGuiWindowFlags_UnsavedDocument = 1 << 20,  // Append '*' to title without affecting the ID, as a convenience to avoid using the ### operator. When used in a tab/docking context, tab is selected on closure and closure is deferred by one frame to allow code to cancel the closure (with a confirmation popup, etc.) without flicker.
        ImGuiWindowFlags_NoDocking = 1 << 21,  // Disable docking of this window

        ImGuiWindowFlags_NoNav = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
        ImGuiWindowFlags_NoDecoration = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse,
        ImGuiWindowFlags_NoInputs = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,

        // [Internal]
        ImGuiWindowFlags_NavFlattened = 1 << 23,  // [BETA] Allow gamepad/keyboard navigation to cross over parent border to this child (only use on child that have no scrolling!)
        ImGuiWindowFlags_ChildWindow = 1 << 24,  // Don't use! For internal use by BeginChild()
        ImGuiWindowFlags_Tooltip = 1 << 25,  // Don't use! For internal use by BeginTooltip()
        ImGuiWindowFlags_Popup = 1 << 26,  // Don't use! For internal use by BeginPopup()
        ImGuiWindowFlags_Modal = 1 << 27,  // Don't use! For internal use by BeginPopupModal()
        ImGuiWindowFlags_ChildMenu = 1 << 28,  // Don't use! For internal use by BeginMenu()
        ImGuiWindowFlags_DockNodeHost = 1 << 29   // Don't use! For internal use by Begin()/NewFrame()

        // [Obsolete]
        //ImGuiWindowFlags_ShowBorders          = 1 << 7,   // --> Set style.FrameBorderSize=1.0f / style.WindowBorderSize=1.0f to enable borders around windows and items
        //ImGuiWindowFlags_ResizeFromAnySide    = 1 << 17,  // --> Set io.ConfigWindowsResizeFromEdges and make sure mouse cursors are supported by back-end (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors)
    };


    public static class ImGui
    {

        [DllImport("__Internal", EntryPoint = "PBegin")]
        public static extern bool Begin(string name, ref bool open, ImGuiWindowFlags flags = 0);

        [DllImport("__Internal", EntryPoint = "PEnd")]
        public static extern void End();

        [DllImport("__Internal", EntryPoint = "PBeginMenuBar")]
        public static extern bool BeginMenuBar();

        [DllImport("__Internal", EntryPoint = "PEndMenuBar")]
        public static extern void EndMenuBar();

        [DllImport("__Internal", EntryPoint = "PBeginMenu")]
        public static extern bool BeginMenu(string name);

        [DllImport("__Internal", EntryPoint = "PEndMenu")]
        public static extern void EndMenu();

        [DllImport("__Internal", EntryPoint = "PMenuItem")]
        public static extern bool MenuItem(string name);

        [DllImport("__Internal", EntryPoint = "PBeginChild")]
        public static extern bool BeginChild(string id, ImGuiWindowFlags flags = 0, Vector2 size = new Vector2(), bool border = false);

        [DllImport("__Internal", EntryPoint = "PEndChild")]
        public static extern void EndChild();
        [DllImport("__Internal", EntryPoint = "PImage")]
        static extern void PImage(IntPtr tex, ref Vector2 size, ref Vector2 uv0, ref Vector2 uv1);

        //PImage(Texture2D* tex, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1)
        public static void Image(Texture2D texture, Vector2 size, Vector2 uv0, Vector2 uv1)
        {
            PImage(texture.GetNativeObject(), ref size, ref uv0, ref uv1);
        }

        [DllImport("__Internal", EntryPoint = "PGetWindowSize")]
        static extern void PGetWindowSize(out Vector2 size);

        public static Vector2 GetWindowSize()
        {
            PGetWindowSize(out Vector2 size);
            return size;
        }


        [DllImport("__Internal", EntryPoint = "PIsWindowDocked")]
        public static extern bool IsWindowDocked();
        [DllImport("__Internal", EntryPoint = "PButton")]
        public static extern bool Button(string name);
        [DllImport("__Internal", EntryPoint = "PSameLine")]
        public static extern void SameLine();

        [DllImport("__Internal", EntryPoint = "PSetWindowSize")]
        public static extern void SetWindowSize(Vector2 size);
        [DllImport("__Internal", EntryPoint = "PBeginGroup")]
        public static extern void BeginGroup();
        [DllImport("__Internal", EntryPoint = "PEndGroup")]
        public static extern void EndGroup();


    }
}

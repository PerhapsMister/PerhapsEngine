using System;
using System.Runtime.InteropServices;
using System.Numerics;
using System.Collections.Generic;
using System.Text;

namespace Perhaps.Engine
{
    #region Enums
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

    public enum ImGuiKey
    {
        ImGuiKey_Tab,
        ImGuiKey_LeftArrow,
        ImGuiKey_RightArrow,
        ImGuiKey_UpArrow,
        ImGuiKey_DownArrow,
        ImGuiKey_PageUp,
        ImGuiKey_PageDown,
        ImGuiKey_Home,
        ImGuiKey_End,
        ImGuiKey_Insert,
        ImGuiKey_Delete,
        ImGuiKey_Backspace,
        ImGuiKey_Space,
        ImGuiKey_Enter,
        ImGuiKey_Escape,
        ImGuiKey_KeyPadEnter,
        ImGuiKey_A,         // for text edit CTRL+A: select all
        ImGuiKey_C,         // for text edit CTRL+C: copy
        ImGuiKey_V,         // for text edit CTRL+V: paste
        ImGuiKey_X,         // for text edit CTRL+X: cut
        ImGuiKey_Y,         // for text edit CTRL+Y: redo
        ImGuiKey_Z,         // for text edit CTRL+Z: undo
        ImGuiKey_COUNT
    };

    public enum ImGuiInputTextFlags
    {
        ImGuiInputTextFlags_None = 0,
        ImGuiInputTextFlags_CharsDecimal = 1 << 0,   // Allow 0123456789.+-*/
        ImGuiInputTextFlags_CharsHexadecimal = 1 << 1,   // Allow 0123456789ABCDEFabcdef
        ImGuiInputTextFlags_CharsUppercase = 1 << 2,   // Turn a..z into A..Z
        ImGuiInputTextFlags_CharsNoBlank = 1 << 3,   // Filter out spaces, tabs
        ImGuiInputTextFlags_AutoSelectAll = 1 << 4,   // Select entire text when first taking mouse focus
        ImGuiInputTextFlags_EnterReturnsTrue = 1 << 5,   // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider looking at the IsItemDeactivatedAfterEdit() function.
        ImGuiInputTextFlags_CallbackCompletion = 1 << 6,   // Callback on pressing TAB (for completion handling)
        ImGuiInputTextFlags_CallbackHistory = 1 << 7,   // Callback on pressing Up/Down arrows (for history handling)
        ImGuiInputTextFlags_CallbackAlways = 1 << 8,   // Callback on each iteration. User code may query cursor position, modify text buffer.
        ImGuiInputTextFlags_CallbackCharFilter = 1 << 9,   // Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
        ImGuiInputTextFlags_AllowTabInput = 1 << 10,  // Pressing TAB input a '\t' character into the text field
        ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 11,  // In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).
        ImGuiInputTextFlags_NoHorizontalScroll = 1 << 12,  // Disable following the cursor horizontally
        ImGuiInputTextFlags_AlwaysInsertMode = 1 << 13,  // Insert mode
        ImGuiInputTextFlags_ReadOnly = 1 << 14,  // Read-only mode
        ImGuiInputTextFlags_Password = 1 << 15,  // Password mode, display all characters as '*'
        ImGuiInputTextFlags_NoUndoRedo = 1 << 16,  // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().
        ImGuiInputTextFlags_CharsScientific = 1 << 17,  // Allow 0123456789.+-*/eE (Scientific notation input)
        ImGuiInputTextFlags_CallbackResize = 1 << 18,  // Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
                                                       // [Internal]
        ImGuiInputTextFlags_Multiline = 1 << 20,  // For internal use by InputTextMultiline()
        ImGuiInputTextFlags_NoMarkEdited = 1 << 21   // For internal use by functions using InputText() before reformatting data
    };


    #endregion


    public static class ImGui
    {

        [DllImport("__Internal", EntryPoint = "PBegin")]
        public static extern bool Begin(string name, ref bool open, ImGuiWindowFlags flags = 0);
        [DllImport("__Internal", EntryPoint = "PBegin_NoRef")]
        public static extern bool Begin(string name, ImGuiWindowFlags flags = 0);


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
        [DllImport("__Internal", EntryPoint = "PTreeNode")]
        public static extern bool TreeNode(string name);
        [DllImport("__Internal", EntryPoint = "PTreePop")]
        public static extern void PopTree();



        [DllImport("__Internal", EntryPoint = "PColumns")]
        public static extern void Columns(int count, string id = null);
        [DllImport("__Internal", EntryPoint = "PPushId")]
        public static extern void PushId(int id);
        [DllImport("__Internal", EntryPoint = "PPushId_str")]
        public static extern void PushId(string id);
        [DllImport("__Internal", EntryPoint = "PPopId")]
        public static extern void PopId();

        [DllImport("__Internal", EntryPoint = "PSelectable")]
        public static extern bool Selectable(string name, ref bool selected);
        [DllImport("__Internal", EntryPoint = "PSelectable_NotRef")]
        static extern bool PSelectable_NotRef(string name, bool selected);
        public static bool Selectable(string name, bool selected)
        {
            return PSelectable_NotRef(name, selected);
        }
        [DllImport("__Internal", EntryPoint = "PIsItemClicked")]
        public static extern bool IsItemClicked(int mouseButton);

        [DllImport("__Internal", EntryPoint = "POpenPopup")]
        public static extern void OpenPopup(string id);

        [DllImport("__Internal", EntryPoint = "PCloseCurrentPopup")]
        public static extern void CloseCurrentPopup();

        [DllImport("__Internal", EntryPoint = "PBeginPopup")]
        public static extern bool BeginPopup(string id, ImGuiWindowFlags flags = 0);

        [DllImport("__Internal", EntryPoint = "PEndPopup")]
        public static extern void EndPopup();
        [DllImport("__Internal", EntryPoint = "PBeginDragSource")]
        public static extern bool BeginDragSource();
        [DllImport("__Internal", EntryPoint = "PEndDragAndDropSource")]
        public static extern void EndDragAndDropSource();
        [DllImport("__Internal", EntryPoint = "PBeginDragAndDropTarget")]
        public static extern bool BeginDragAndDropTarget();
        [DllImport("__Internal", EntryPoint = "PEndDragAndDropTarget")]
        public static extern void EndDragAndDropTarget();
        [DllImport("__Internal", EntryPoint = "PNextColumn")]
        public static extern void NextColumn();



        [DllImport("__Internal", EntryPoint = "PSetDragAndDropPayload")]
        public static extern bool PSetDragAndDropPayload(string id, int payloadData);


        static Dictionary<int, object> dataStorage = new Dictionary<int, object>();
        public static bool SetDragAndDropPayload(string id, object payloadData = null)
        {
            int payloadId = -1;
            if (payloadData != null)
            {
                Random r = new Random();
                

                payloadId = r.Next(int.MinValue, int.MaxValue);
                if (!dataStorage.ContainsKey(payloadId))
                    dataStorage.Add(payloadId, null);

                dataStorage[payloadId] = payloadData;
            }

            return PSetDragAndDropPayload(id, payloadId);
        }

        [DllImport("__Internal", EntryPoint = "PAcceptDragAndDropPayload")]
        static extern bool PAcceptDragAndDropPayload(string id, ref int dataId);

        public static bool AcceptDragAndDropPayload(string id, out object payloadData)
        {
            int dataId = 0;
            payloadData = null;
            bool val = PAcceptDragAndDropPayload(id, ref dataId);
            if (val && dataId != 0)
            {
                if (dataStorage.ContainsKey(dataId))
                {
                    payloadData = dataStorage[dataId];
                    dataStorage.Remove(dataId);
                }
            }

            return val;
        }

        [DllImport("__Internal", EntryPoint = "PText")]
        public static extern void Text(string text = "");

        [DllImport("__Internal", EntryPoint = "PBulletText")]
        public static extern void BulletText(string text);
        [DllImport("__Internal", EntryPoint = "PBullet")]
        public static extern void Bullet();


        [DllImport("__Internal", EntryPoint = "PInputText")]
        public static extern bool PInputText(string label, StringBuilder text, int length, ImGuiInputTextFlags flags);

        const int max_chars = 512;
        static StringBuilder buffer = new StringBuilder(max_chars);
        public static bool InputText(string label, ref string inputText, ImGuiInputTextFlags flags = 0)
        {
            buffer.Clear();
            buffer.Append(inputText);

            bool val = PInputText(label, buffer, buffer.Capacity, flags);
            inputText = buffer.ToString();

            return val;

        }

        [DllImport("__Internal", EntryPoint = "PPushItemWidth")]
        public static extern void PushItemWidth(float width);

        [DllImport("__Internal", EntryPoint = "PPopItemWidth")]
        public static extern void PopItemWidth();

        [DllImport("__Internal", EntryPoint = "PSeparator")]
        public static extern void Separator();

        [DllImport("__Internal", EntryPoint = "PIsKeyPressed")]
        public static extern bool IsKeyPressed(ImGuiKey key);

        [DllImport("__Internal", EntryPoint = "PIsKeyDown")]
        public static extern bool PIsKeyDown(ImGuiKey key);

        [DllImport("__Internal", EntryPoint = "PIsMouseDoubleClicked")]
        public static extern bool IsMouseDoubleClicked(int mouseButton);

        [DllImport("__Internal", EntryPoint = "PPushAllowKeyboardFocus")]
        public static extern bool PushAllowKeyboardFocus(bool allowKeyboardFocus);

        [DllImport("__Internal", EntryPoint = "PPopAllowKeyboardFocus")]
        public static extern bool PopAllowKeyboardFocus();


        [DllImport("__Internal", EntryPoint = "PSetKeyboardFocusHere")]
        public static extern bool SetKeyboardFocusHere();

    }
}

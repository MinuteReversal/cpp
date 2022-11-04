# create control to mfc
1. add member (CButton).
2. call (CButton) Create in Create Life Cycle, Style WS_Child | WS_Visible | BS_PUSHBUTTON , CRect(0,0,120,30)
2. add ON_COMMAND(IDC_XXX,&ClassName::MethodName)
3. add handler method
' This script prompts the user to select the PhysX SDK directory so that 
' the nxpath.vsprops files may be updated within the APEX compiler folders.
' The user may also choose to edit the nxpath.vsprops files by hand.

'WScript.Echo "Hello World"


Const NxPathFile="nxpath.vsprops"

Set objShell = CreateObject("Shell.Application")
Set objFSO = CreateObject("Scripting.FileSystemObject")
Set objReg = CreateObject("vbscript.regexp")

' Get the PhysX SDK folder
browseForFolderStr = "Select the PhysX SDK folder. This folder will be written to the nxpath.vsprops files in the APEX projects folders so APEX can find required PhysX headers and libs."
Set objFolder = objShell.BrowseForFolder(0, browseForFolderStr, 16, 17)
If objFolder Is Nothing Then
	Wscript.Quit
End If

' Find all of the nxpath.vsprops files

Dim NxPathFileList()
FileCounter = 0
' Update the nxpath.vsprops files 

UpdateNxPathsInCompilerFolder("compiler")
UpdateNxPathsInCompilerFolder("samples\compiler")

If FileCounter > 0 Then
	UpdatedFileMsg = "These files were updated:" & Chr(10)
	For Each iPath In  NxPathFileList
		UpdatedFileMsg = UpdatedFileMsg & iPath & Chr(10)
	Next
	UpdatedFileMsg = UpdatedFileMsg & "With this PhysX SDK path: " & Chr(10) & objFolder.self.path
Else
	UpdatedFileMsg = "No " & NxPathFile & " files were updated."
End If
	Wscript.echo UpdatedFileMsg

WScript.Quit


'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Given a CompilerFolder, this subroutine will go through the subfolders
' and update any nxpaths.vsprops files it finds with the new PhysX SDK folder
' input: 
'	CompilerFolder
' expected globals: 
'	NxPathFile
'	objFSO
'	objDir
'	objReg
'	FileCounter
'	NxPathFileList
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Sub UpdateNxPathsInCompilerFolder(CompilerFolder)
	Const ForReading = 1
	Const ForWriting = 2

	
	' If the folder doesn't exist exit the subroutine
	If Not objFSO.FolderExists(CompilerFolder) Then
		Exit Sub
	End If

	Set objDir = objFSO.GetFolder(CompilerFolder)
	For Each iProjectFolder In objDir.SubFolders
		filePath = iProjectFolder.Path & "\" & NxPathFile
		If objFSO.FileExists(filePath) Then
			
			' Append this file path to the list of files that were changed
			FileCounter = FileCounter + 1
			ReDim Preserve NxPathFileList(FileCounter)
			NxPathFileList(FileCounter-1) = filePath
			
			
			Set myFile = objFSO.OpenTextFile(filePath, ForReading, True)
			Set myTemp= objFSO.OpenTextFile(filePath & ".tmp", ForWriting, True)
			Do While Not myFile.AtEndofStream
				myLine = myFile.ReadLine

				' Test VC10 vsprops file
				objReg.Pattern = "<NXPATH>.*"
				If objReg.Test(myLine) Then
					myLine = objReg.Replace(myLine, "<NXPATH>" & objFolder.self.path & "</NXPATH>")
				End If
				
				myTemp.WriteLine myLine
			Loop

			myFile.Close
			myTemp.Close

			' Replace the original file with the updated tmp file, delete the tmp file
			objFSO.DeleteFile(filePath)
			objFSO.MoveFile filePath&".tmp", filePath
		End If	
	Next

End Sub

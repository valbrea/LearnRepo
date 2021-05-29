function associateFiles(action, userExtList, fileStr)
 
% associateFiles(action, extList, ddecd, fileStr)
%
% Makes a registry files that can be used to set correct file associations on
% a windows platform. The following MATLAB file extensions are supported:
% .fig          - MATLAB Figure
% .m            - MATLAB Code
% .mat          - MATLAB Data
% .mdl          - Simulink Model (MDL format)
% .mdlp         - Simulink Protected Model
% .mexw64       - MATLAB MEX
% .mlapp        - MATLAB App
% .mlappinstall - MATLAB App Installer
% .mldatx       - MATLAB Data Export File
% .mlpkginstall - MATLAB Support Package Installer
% .mlproj       - MATLAB Project Archive
% .mltbx        - MATLAB Toolbox
% .mlx          - MATLAB Live Script
% .mn           - MuPAD Notebook
% .p            - MATLAB P-code
% .req          - MATLAB Traceability File
% .sbproj       - SimBiology Project
% .sfx          - Stateflow Chart
% .sldd         - Simulink Data Dictionary
% .slddc        - Simulink Data Dictionary Cache
% .slmx         - MATLAB Traceability File
% .slreqx       - Simulink Requirements data file
% .sltx         - Simulink Template
% .slx          - Simulink Model
% .slxc         - Simulink Cache
% .slxp         - Simulink Protected Model File
% .ssc          - Simscape Model
%
% Grandfathered extensions (R2020a), kept for backward compatibility
% .mexw32 - MATLAB MEX (32-bit no longer supported)
% .mlprj  - MATLAB Project (renamed .mlproj)
% .mu     - MuPAD Code (MuPAD notebook replaced by MATLAB Live Script)
% .muphlp - MuPAD Help (MuPAD notebook replaced by MATLAB Live Script)
% .xvc    - MuPAD Graphics (MuPAD notebook replaced by MATLAB Live Script)
% .xvz    - MuPAD Graphics (MuPAD notebook replaced by MATLAB Live Script)
%
% INPUT:
% action    - optional string.
%             * 'add' (default) adds/rewrites the MATLAB file association
%               registry keys for this version.
%             * 'delete' deletes the MATLAB file association registry
%                entries for ALL versions of MATLAB (including "old style"
%                ones)
%             * 'deleteadd' is the same as 'delete' followed by 'add'
% extList   - optional string or cell array of strings containing the file
%             extensions that should be associated with this version. Default is
%             all MATLAB file extension (see above).
% fileStr -   optional string with the name of the registry file to be written
%             (possibly including path). Default is the file
%             'MatlabFileAssocFix.reg' in the current directory.
%
% USAGE:
% 1) In the MATLAB command window browse to the folder where this file is
%    located.
% 2) Run with desired options (see above). A registry file should have been
%    created.
% 3) Exit all running instances of MATLAB.
% 4) Make a backup copy of the windows registry if you need to restore the
%    changes, see https://support.microsoft.com/en-us/kb/322756
% 5) Double click on the created file (possibly need to enter a password) and
%    confirm.
% 6) Restart Windows (or explorer.exe).
% 7) The MATLAB files should now be associated with the MATLAB version that the
%    registry file was created in and e.g. m-files should be opened in an
%    already running instance of MATLAB.
%
% EXAMPLES:
% * associateFiles('deleteadd') - Makes a registry files that deletes all
%   previous MATLAB file association registry keys and write new ones that
%   associates all MATLAB files with the MATLAB version that the registry file
%   was created in.
% * associateFiles('', {'.m', '.mat', '.fig'}, 'myFile') - Makes a
%   registry file "myFile.reg" that associates m-, mat- and fig-files with
%   the MATLAB version that the registry file was created in.
%
% NOTE:
% - Changes the default behaviour for DDE open action on .m files for newer
%   versions of MATLAB. Default is always open in a new editor instance,
%   now the .m file is opened in a new tab in the editor if an instance
%   already exist.
% - Not all defined DDE actions might be work for the used MATLAB
%   version.
% - Once created the registry file might be used across several machines
%   (provided the MATLAB installation on these is the same).
%
% VERSION 2.0
%
% See also <a href="matlab:help createShortcuts">createShortcuts</a>
 
% Author Patrik Forssén, Karlstad University
%
% VERSION HISTORY
% Version 1.0 (11 Jun 2015)
% - First realase
%
% Version 2.0 (7 Oct 2020)
% - File type names updated.
% - Added support for .mlproj, .mlx, .sbproj, .sfx, .slmx, .slreqx, .slxc
%   files.
% - DDE action for .mdl updated
% - DDE actions for .mlapp, .mlappinstall, .mldatx, .mlpkginstall, .mltbx,
%   .sldd, .sltx added
% - Icons from DLL files used if present
% - Added "AppUserModelId" registry key used by later versions of MATLAB
% - Added DDE change to MATLAB for later versions. When a file is opened
%   in Explorer, whitout a running instance of MATLAB, the current
%   directory in MATLAB is changed to that of the file.
 
% Defualt input
if (nargin < 1 || isempty(action))   , action      = 'add'; end
if (nargin < 2)                      , userExtList = {}   ; end
if (nargin < 3)                      , fileStr     = ''   ; end
if (~iscell(userExtList))
  if (isempty(userExtList))
    userExtList = {};
  else
    userExtList = {userExtList};
  end
end
 
% Sanity check
if (~ischar(action) || (~strcmpi(action, 'add') && ...
    ~strcmpi(action, 'delete') && ~strcmpi(action, 'deleteadd')))
  error('associateFiles:incorrectValue', ['The action to perform must ', ...
    'be a string ''add'', ''delete'' or ''deleteadd''!'])
end
if (~isempty(userExtList) && ~min(cellfun(@ischar, userExtList)))
  error('associateFiles:incorrectType', ['The file extension list must ', ...
    'be a string or a cell array of strings!'])
end
if (~ischar(fileStr))
  error('associateFiles:incorrectType', ...
    'The file to write to must be a string!')
end
 
 
% Get the currently running MATLAB version
verStr = regexp(version, '(\d*?\.\d*?\.\d*?)\.', 'tokens');
verStr = verStr{1}{1};
verNum = str2double(regexprep(verStr, '(\d*?\.\d*)[\x0000-\xffff]*', '$1'));
verHex = sprintf('%04x', str2double(regexprep(verStr, ...
  '(\d*?)\.[\x0000-\xffff]*', '$1')), str2double(regexprep(verStr, ...
  '\d*?\.(\d*?)\.[\x0000-\xffff]*', '$1')));
% Release
relStr = ['R', version('-release')];
 
% Get 32/64-bit
arch = computer;
switch arch
  case 'PCWIN'
    binFolder = 'win32';  % Older versions!
  case 'PCWIN64'
    binFolder = 'win64';
  otherwise
    error('Sorry, only windows platform supported!')
end
binPath = fullfile(matlabroot, 'bin', binFolder);
% DLL plugins present?
dllPath = fullfile(binPath, 'osintegplugins', 'osintegplugins');
if (~exist(dllPath, 'dir'))
  dllPath = [];
end
 
 
% Known MATLAB files with possible DDE actions
fileExtCell = {...
  'fig'         , 'MATLAB Figure'                   , '-62', ...
  {'Open', 'uiopen(''%1'',1)'}      , []; ...
  'm'           , 'MATLAB Code'                     , '-58', ...
  {'Open', 'uiopen(''%1'',1)'}      , {'Run', 'run(''%1'')'}; ...
  'mat'         , 'MATLAB Data'                     , '-59', ...
  {'Load', 'load(''%1'')'}          , {'Open', 'uiimport(''%1'')'}; ...
  'mdl'         , 'Simulink Model (MDL format)'     , '-61', ...
  {'Open', 'uiopen(''%1'',1)'}      , []; ...
  'mdlp'        , 'Simulink Protected Model'        , '-72', ...
  []                                , []; ...
  'mexw64'      , 'MATLAB MEX'                      , '-63', ...
  []                                , []; ...
  'mlapp'       , 'MATLAB App'                      , 'XX' , ...
  {'Edit', 'uiopen(''%1'',1)'}      , {'Open', 'run(''%1'')'}; ...
  'mlappinstall', 'MATLAB App Installer'            , 'XX' , ...
  {'Install', 'uiopen(''%1'',1)'}   , []; ...
  'mldatx'      , 'MATLAB Data Export File'         , 'XX' , ...
  {'Open', 'uiopen(''%1'',1)'}      , ...
  {'Run' , 'matlabshared.mldatx.internal.run(''%1'')'}; ...
  'mlpkginstall', 'MATLAB Support Package Installer', 'XX' , ...
  {'Install', 'uiopen(''%1'',1)'} , {'Open', 'uiopen(''%1'',1)'}; ...
  'mlproj'      , 'MATLAB Project Archive'          , 'XX' , ...
  {'Open', 'uiopen(''%1'',1)'}      , []; ...
  'mltbx'       , 'MATLAB Toolbox'                  , 'XX' , ...
  {'Install', 'uiopen(''%1'',1)'}   , []; ...
  'mlx'         , 'MATLAB Live Script'              , 'XX' , ...
  {'Open', 'uiopen(''%1'',1)'}      , []; ...
  'mn'          , 'MuPAD Notebook'                  , '-66', ...
  {'Open', 'uiopen(''%1'',1)'}      , []; ...
  'p'           , 'MATLAB P-code'                   , '-60', ...
  []                                , []; ...
  'req'         , 'MATLAB Traceability File'        , []   , ...
  []                                , []; ...
  'sbproj'      , 'SimBiology Project'              , 'XX' , ...
  {'Open', 'simbiology(''%1'')'}    , []; ...
  'sfx'         , 'Stateflow Chart'                 , 'XX' , ...
  {'Open', 'uiopen(''%1'',1)'}      , []; ...
  'sldd'        , 'Simulink Data Dictionary'        , 'XX' , ...
  {'Open', 'uiopen(''%1'',1)'}      , []; ...
  'slddc'       , 'Simulink Data Dictionary Cache'  , []   , ...
  []                                , []; ...
  'slmx'        , 'MATLAB Traceability File'        , []   , ...
  []                                , []; ...
  'slreqx'      , 'Simulink Requirements data file' , []   , ...
  []                                , []; ...
  'sltx'        , 'Simulink Template'               , 'XX' , ...
  {'Open', 'uiopen(''%1'',1)'}      , []; ...
  'slx'         , 'Simulink Model'                  , '-73', ...
  {'Open', 'uiopen(''%1'',1)'}      , []; ...
  'slxc'        , 'Simulink Cache'                  , []   , ...
  []                                , []; ...
  'slxp'        , 'Simulink Protected Model File'   , []   , ...
  []                                , []; ...
  'ssc'         , 'Simscape Model'                  , '-65', ...
  {'Open', 'uiopen(''%1'',1)'}      , []; ...
  'mexw32'      , 'MATLAB MEX'                      , '-63', ...
  []                                , []; ...
  'mlprj'       , 'MATLAB Project'                  , []   , ....
  []                                , []; ...
  'mu'          , 'MuPAD Code'                      , '-67', ...
  {'Open', 'uiopen(''%1'',1)'}      , []; ...
  'muphlp'      , 'MuPAD Help'                      , '-68', ...
  {'Open', 'doc(symengine, ''%1'')'}, []; ...
  'xvc'         , 'MuPAD Graphics'                  , '-69', ...
  {'Open', 'mupad(''%1'')'}         , []; ...
  'xvz'         , 'MuPAD Graphics'                  , '-70', ...
  {'Open', 'mupad(''%1'')'}         , []};
 
% Possibly trim list
if (~isempty(userExtList))
  fileExtCell = fileExtCell(ismember(fileExtCell(:, 1), ...
    regexprep(userExtList, '\.', '')), :);
end
 
% Make registry file
if (~isempty(fileStr))
  % Possibly add/change file extension
  [filePath, fileName] = fileparts(fileStr);
  fileStr = fullfile(filePath, [fileName, '.reg']);
  fid     = fopen(fileStr, 'w');
else
  fid     = fopen('MatlabFileAssocFix.reg', 'w');
end
if (fid == -1)
  error('associateFiles:openFile', 'Failed to create registry file!')
end
% Write initial lines
fprintf(fid, '%s\r\n\r\n', 'Windows Registry Editor Version 5.00');
fprintf(fid, '%s\r\n\r\n', ';FIXES MATLAB FILE ASSOCIATIONS');
 
 
% REMOVE OLD KEYS
explorerKey = ['HKEY_CURRENT_USER\Software\Microsoft\Windows\', ...
  'CurrentVersion\Explorer\FileExts'];
% Iterate over file extensions
for fileExtNo = 1 : size(fileExtCell, 1)
  rmKeys  = {};
  fileExt = fileExtCell{fileExtNo, 1};
  
  % File extension keys
  [status, result] = dos(['reg query HKEY_CLASSES_ROOT /f .', fileExt, ...
    ' /k /e']);
  if (~status)
    keys = regexp(result, '(HKEY_CLASSES_ROOT[\x0000-\xffff]*?)\n', 'tokens');
    rmKeys = [rmKeys, keys{:}];
  end
  
  % Old style keys without version numbers
  if (~strcmpi(fileExt, 'mexw64'))
    % Uses single DDE key for mex files
    if (strcmpi(fileExt, 'mexw32'))
      fileExtTmp = 'mex';
    else
      fileExtTmp = fileExt;
    end
    [status, result] = dos(['reg query HKEY_CLASSES_ROOT /f ', ...
      fileExtTmp, 'file /k /e']);
    if (~status)
      keys = regexp(result, '(HKEY_CLASSES_ROOT[\x0000-\xffff]*?)\n', ...
        'tokens');
      rmKeys = [rmKeys, keys{:}];
    end
  end
  
  % New style keys with version number
  if (strcmpi(action, 'add'))
    % Only remove keys related to this version
    [status, result] = dos(['reg query HKEY_CLASSES_ROOT /f MATLAB.', ...
      fileExt, '.', verStr ' /k']);
  else
    % Remove keys related to ALL version
    [status, result] = dos(['reg query HKEY_CLASSES_ROOT /f MATLAB.', ...
      fileExt, '. /k']);
  end
  if (~status)
    keys = regexp(result, '(HKEY_CLASSES_ROOT[\x0000-\xffff]*?)\n', 'tokens');
    rmKeys = [rmKeys, keys{:}];
  end
  
  % Explorer keys
  [status, result] = dos(['reg query ', explorerKey, ' /f .', fileExt, ...
    ' /k /e']);
  if (~status)
    keys = regexp(result, '(HKEY_CURRENT_USER[\x0000-\xffff]*?)\n', 'tokens');
    rmKeys = [rmKeys, keys{:}];
  end
  
  % Write to file
  if (~isempty(rmKeys))
    fprintf(fid, '%s\r\n\r\n', [';REMOVES ', upper(fileExt), ...
      ' FILE ASSOCIATIONS']);
    for keyNo = 1 : length(rmKeys)
      key = rmKeys{keyNo};
      fprintf(fid, '%s\r\n\r\n', ['[-', key, ']']);
    end
  end
end
 
 
% ADD KEYS
dummyCount = 73;
if (~strcmpi(action, 'delete'))
  % Get text Persistent Handler
  [status, result] = dos(...
    'reg query HKEY_CLASSES_ROOT\.txt\PersistentHandler /ve');
  if (~status)
    PersistentHandler = regexp(result, '\{[\x0000-\xffff]*?\}', 'match');
    PersistentHandler = PersistentHandler{1};
  else
    PersistentHandler = '';
  end
  % DDE call
  ddeCall = 'ShellVerbs.Matlab';
  if (verNum > 8)
    % Changed from R2013a
    ddeCall = [ddeCall, '.', verStr];
  end
  % DDE change directory string
  if (verNum >= 9.8)
    % Changes MATLAB directory to the files ones when DDE action is applied
    % without a running MATLAB instance. Don't know the version when this
    % was changed, but at least from release 2020a.
    ddeDirStr = [' -r  \"eval(''[WinReg_path,WinReg_name,WinReg_ext]=', ...
      'fileparts(''''%1'''');cd(WinReg_path);clear WinReg_path ', ...
      'WinReg_name WinReg_ext'');\""'];
  else
    ddeDirStr = '"';
  end
  % Path with \\
  binPathStr = regexprep(binPath, '\\', '\\\\');
  % Default icon
  defIconStr  = [];
  defIconFile = fullfile(binPath, 'm.ico');
  if (exist(defIconFile, 'file'))
    defIconStr = ['"', binPathStr, 'm.ico,0"'];
  end
  if (~isempty(dllPath))
    defIconDLL = fullfile(dllPath, 'm', 'mwmfaplugin.dll');
    if (exist(defIconDLL, 'file'))
      defIconStr = ['"\"', regexprep(defIconDLL, '\\', '\\\\'), '\",0"'];
    end
  end
  % Default icon for .mex32
  defMex32IconStr  = [];
  defMex32IconFile = fullfile(binPath, 'mexw32.ico');
  if (~exist(defMex32IconFile, 'file'))
    % Use same as for mexw64 if it exist
    mex64IconFile = fullfile(binPath, 'mexw64.ico');
    if (exist(mex64IconFile, 'file'))
      defMex32IconStr = ['"', binPathStr, 'mexw64.ico,0"'];
    end
  end
  if (~isempty(dllPath))
    defMex32DLL = fullfile(dllPath, 'mexw32', 'mwmexw32faplugin.dll');
    if (~exist(defMex32DLL, 'file'))
      % Use same as for mexw64 if it exist
      mex64DLL = fullfile(dllPath, 'mexw64', 'mwmexw64faplugin.dll');
      if (exist(mex64DLL, 'file'))
        defMex32IconStr = ['"\"', regexprep(mex64DLL, '\\', '\\\\'), '\",0"'];
      end
    end
  end
  
  % Key for newer version
  appUserModelId = ['"Mathworks.MATLAB.MATLAB.', relStr, '"'];
  
  % Write Shell Open key
  key = ['[HKEY_CLASSES_ROOT\Applications\MATLAB.exe\shell\open', ...
    '\command]%r', '@="\"', binPathStr, '\\MATLAB.exe\" \"%1\""%r%r'];
  fprintf(fid, '%s\r\n\r\n', ';ADD SHELL OPEN');
  lines = regexp(key, '([\x0000-\xffff]*?)%r', 'tokens');
  for lineNo = 1 : length(lines)
    fprintf(fid, '%s\r\n', lines{lineNo}{1});
  end
  
  % Iterate over file types
  for fileExtNo = 1 : size(fileExtCell, 1)
    ddeData = fileExtCell(fileExtNo, :);
    fileExt = ddeData{1};
    
    % File extension keys
    key  = ['[HKEY_CLASSES_ROOT\.', fileExt, ']%r@="MATLAB.', ...
      fileExt, '.', verStr, '"%r'];
    if (strcmpi(fileExt, 'm') && ~isempty(PersistentHandler))
      % Add some values
      key = [key, '"Content Type"="text/plain"%r', ...
        '"PerceivedType"="Text"%r'];
    end
    key = [key, '%r'];
    % Not present on newer versions
    key = [key, '[HKEY_CLASSES_ROOT\.', fileExt, ...
      '\OpenWithProgids]%r"MATLAB.', fileExt, '.', verStr, '"=""%r%r'];
    if (strcmpi(fileExt, 'm') && ~isempty(PersistentHandler))
      key = [key, '[HKEY_CLASSES_ROOT\.', fileExt, ...
        '\PersistentHandler]%r@="', PersistentHandler, '"%r%r'];
    end
    % Not present on newer versions
    key = [key, '[HKEY_CLASSES_ROOT\.', fileExt, ...
      '\Versions\MATLAB.', fileExt, '.' verStr, ...
      ']%r"FileVersionMS"=dword:', verHex, ...
      '%r"FileVersionLS"=dword:00000000%r%r'];
    
    % DDE keys
    key = [key, '[HKEY_CLASSES_ROOT\MATLAB.', fileExt, '.' verStr, ...
      ']%r@="', ddeData{2}, '"%r'];
    dllFlag = 0;
    if (~isempty(dllPath))
      currDLL = fullfile(dllPath, fileExt, ['mw', fileExt, 'faplugin.dll']);
      if (exist(currDLL, 'file')), dllFlag = 1; end
    end
    if (~dllFlag)
      % Older style
      if (~isempty(ddeData{3}))
        if (strcmpi(ddeData{3}, 'XX'))
          % Just use some dummy value, this value is not needed for newer 
          % versions (and hopefully will work if needed...)
          dummyCount = dummyCount + 1;
          ddeData{3} = ['-', num2str(dummyCount)];
        end
        key = [key, '"FriendlyTypeName"="@', binPathStr, '\\matlab.exe', ...
          ',', ddeData{3}, '"%r'];
      end
    else
      % New DLL style
      key = [key, '"FriendlyTypeName"="@', ...
        regexprep(currDLL, '\\', '\\\\'), ',0"%r'];
    end
    % Only present on newer version and when we have DDE action
    if (~isempty(ddeData{4}))
      key = [key, '"AppUserModelId"=', appUserModelId, '%r'];
    end
    key = [key, '%r'];
    
    % Icon
    if (~dllFlag)
      icon = fileExt;
      if (~exist(fullfile(binPath, [icon, '.ico']), 'file'))
        if (strcmpi(fileExt, 'mexw32') && ~isempty(defMex32IconStr))
          % Special case for mex32
          key = [key, '[HKEY_CLASSES_ROOT\MATLAB.', fileExt, '.', verStr, ...
            '\DefaultIcon]%r'];
          key = [key, '@=', defMex32IconStr, '%r%r'];
        elseif (~isempty(defIconStr))
          key = [key, '[HKEY_CLASSES_ROOT\MATLAB.', fileExt, '.', verStr, ...
            '\DefaultIcon]%r'];
          key = [key, '@=', defIconStr, '%r%r'];
        end
      else
        key = [key, '[HKEY_CLASSES_ROOT\MATLAB.', fileExt, '.', verStr, ...
          '\DefaultIcon]%r'];
        key = [key, '@="', binPathStr, '\\', icon, '.ico,0"%r%r'];
      end
    else
      key = [key, '[HKEY_CLASSES_ROOT\MATLAB.', fileExt, '.', verStr, ...
        '\DefaultIcon]%r'];
      key = [key, '@="\"', regexprep(currDLL, '\\', '\\\\'), '\",0"%r%r'];
    end
    % Shell actions
    for shellActionNo = 4:5
      ddePar = ddeData{shellActionNo};
      if (~isempty(ddePar))
        key = [key, '[HKEY_CLASSES_ROOT\MATLAB.', fileExt, '.' verStr, ...
          '\Shell\', ddePar{1}, ']%r@="', ddePar{1}, '"%r%r'];
        key = [key, '[HKEY_CLASSES_ROOT\MATLAB.', fileExt, '.' verStr, ...
          '\Shell\', ddePar{1}, '\command]%r@="\"', binPathStr, ...
          '\\matlab.exe\"', ddeDirStr, '%r%r'];
        key = [key, '[HKEY_CLASSES_ROOT\MATLAB.', fileExt, '.' verStr, ...
          '\Shell\', ddePar{1}, '\ddeexec]%r@="', ddePar{2}, '"%r%r'];
        key = [key, '[HKEY_CLASSES_ROOT\MATLAB.', fileExt, '.' verStr, ...
          '\Shell\', ddePar{1},'\ddeexec\application]%r@="', ...
          ddeCall, '"%r%r'];
        key = [key, '[HKEY_CLASSES_ROOT\MATLAB.', fileExt, '.' verStr, ...
          '\Shell\', ddePar{1},'\ddeexec\topic]%r@="system"%r%r'];
      end
    end
    
    % Explorer keys, not set on newer version of the installer...
    key = [key, '[', explorerKey, '\.', fileExt, '\OpenWithProgids]%r'];
    if (strcmpi(fileExt, 'm'))
      key = [key, '"m_auto_file"=hex(0):%r'];
    end
    key = [key, '"MATLAB.', fileExt, '.',  verStr, '"=hex(0):%r%r'];
    if (~isempty(ddeData{4}))
      % Add key
      key = [key, '[', explorerKey, '\.', fileExt, ...
        '\OpenWithList]%r"a"="MATLAB.exe"%r"MRUList"="a"%r%r'];
    else
      key = [key, '[', explorerKey, '\.', fileExt, '\OpenWithList]%r%r'];
    end
    
    % Write to file
    fprintf(fid, '%s\r\n\r\n', [';ADD ', upper(fileExt), ...
      ' FILE ASSOCIATIONS']);
    lines = regexp(key, '([\x0000-\xffff]*?)%r', 'tokens');
    for lineNo = 1 : length(lines)
      fprintf(fid, '%s\r\n', lines{lineNo}{1});
    end
  end
end
 
% Close file
status = fclose(fid);
if (status == -1)
  warning('associateFiles:closeFile', 'Failed to close registry file')
end
 
end
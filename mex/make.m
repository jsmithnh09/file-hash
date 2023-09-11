function make
  % MAKE generates the MEX file for MEX_MFILEHASH.
  %
  % See Also: MEX
  
  target = 'mex_mfilehash.c';
  rootdir = fileparts(fileparts(mfilename('fullpath')));
  files = {'sha256.c', 'md5.c', 'crc32.c', 'sha1.c'};
  
  % expand the filepath for each source file.
  for fIdx = 1:numel(files)
    files{fIdx} = fullfile(rootdir, 'src', 'hashers', files{fIdx});
  end
  
  % perform the actual MEX compilation.
  fprintf(1, '#### Compiling MFILEHASH\n');
  mex(target, ['-I', fullfile(rootdir, 'include')], ...
      files{:}, '-outdir', fullfile(rootdir, 'mex'));
  
  % now target the UUID portion.
  target = 'mex_uuidrand.c';
  files = {...
      fullfile(rootdir, 'src', 'uuid', 'uuid.c'), ...
      fullfile(rootdir, 'src', 'hashers', 'md5.c'), ...
      fullfile(rootdir, 'src', 'hashers', 'sha1.c')};
  
  fprintf(1, '### Compiling UUIDRAND\n');
  mex(target, ['-I', fullfile(rootdir, 'include')], ...
      files{:}, '-outdir', fullfile(rootdir, 'mex'));
  
  % generate UUID-space MEX using the same files.
  fprintf(1, '### Compiliing UUIDSPACE\n');
  mex('mex_uuidspace.c', ['-I', fullfile(rootdir, 'include')], ...
      files{:}, '-outdir', fullfile(rootdir, 'mex'));


  end
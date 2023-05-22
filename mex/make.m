function make
% MAKE generates the MEX file for MEX_MFILEHASH.
%
% See Also: MEX

target = 'mex_mfilehash.c';
rootdir = fileparts(fileparts(mfilename('fullpath')));
srcdir = fullfile(rootdir, 'src');
files = {'sha256.c', 'md5.c', 'crc32.c', 'sha1.c'};

% expand the filepath for each source file.
for fIdx = 1:numel(files)
  files{fIdx} = fullfile(rootdir, 'src', files{fIdx});
end

% perform the actual MEX compilation.
mex(target, ['-I', srcdir], files{:});
  
end

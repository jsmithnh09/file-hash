function hash = mfilehash(infile, algo)
% MFILEHASH computes a file-hash for use within MATLAB.
%
%   HASH = MFILEHASH(FILNAME[, ALGO])
%       FILENAME (char) is the relative or absolute filepath to hash.
%       ALGO (char) indicates one of the available hashing algorithms.
%           Default: sha256.
%           Available Algorithms include: sha256, md5, sha1, crc32.
%       HASH (char) is the resulting HEX string of the checksum/hash.
%
% See Also: PRIVATE_MFILEHASH

if (exist(infile, 'file') ~= 2)
    error('Input FILE does not exist.');
elseif (nargin < 2)
    algo = 'sha256';
end
hash = mex_mfilehash(infile, algo);

end % mfilehash
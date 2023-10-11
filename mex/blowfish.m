function y = blowfish(x, mode, key)
% BLOWFISH performs blowfish encryption and decryption on real or complex double data.
%
% Y = BLOWFISH(X, MODE, KEY)
%   X (double) is the numeric data to cipher.
%   MODE (char) indicates 'ENC' or 'DEC' to either encode or decode the input data.
%   KEY (char) is the symmetric cipher key Must be 4-61 character ASCII string.
%
% Example:
%   X = randn(10) + randn(10) .* 1i;
%   Xe = blowfish(X, 'enc', 'super-secret');
%   Xd = blowfish(Xe, 'dec', 'super-secret');
%   assert(X == Xd);
%
% Notes:
%   MAKE SURE NOT TO LOSE YOUR KEY. Otherwise, you will not be able to recover
%   your original data.
%
% Blowfish source code GPL licensed (C) 1997 Paul Kocher.
% See Also: MEX_BLOWFISH

if (nargin ~= 3)
    error('blowfish:InvalidSyntax', ...
        'Three input arguments were expected.');
elseif (~ischar(key) || numel(key) < 4 || numel(key) > 61)
    error('blowfish:InvalidSyntax', ...
        'Input KEY must be a 4-61 ASCII string.');
elseif (~strncmpi(mode, 'e', 1) && ~strncmpi(mode, 'd', 1))
    error('blowfish:InvalidSyntax', ...
        'Input operation mode must indicate ''ENC'' or ''DEC''.');
end
y = mex_blowfish(x, mode, key);

end


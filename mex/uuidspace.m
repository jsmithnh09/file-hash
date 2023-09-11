function uuid = uuidspace(instr, vnum, nsid)
% UUIDSPACE generates a UUID version 3 or 5 using a pre-defined UUID namespace.
%
%   UUID = UUIDSPACE(INSTR, VNUM, NSID)
%       INSTR (char) is the input string to use as a seed.
%       VNUM (scalar) indicates version 3 or 5.
%       NSID (sclar) indicates an ID in the range 0-3, (DNS, URL, OID, or X.500.)
%       UUID (char) is the resulting UUID.
%
% See Also: UUIDGEN

    uuid = mex_uuidspace(instr, vnum, nsid);
end
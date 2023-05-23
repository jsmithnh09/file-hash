classdef test_filehash < matlab.unittest.TestCase
    % TEST_FILEHASH to verify the file-hash, data will need to be regenerated using
    % the file_hash.py with python3.
    %
    % See Also: MFILEHASH, MEX_MFILEHASH   
    properties(Constant)
        ALGORITHMS = {'SHA1', 'SHA256', 'MD5', 'CRC32'};
        PS_PRINTF = 'Get-FileHash %s -Algorithm %s';
        TEST_FILE = fullfile(fileparts(mfilename('fullpath')), 'test.txt');
        RESULTS_FILE = fullfile(fileparts(mfilename('fullpath')), 'results.json');
    end

    properties
        file_hashes struct
    end


    methods(TestClassSetup)
        function read_testfile(testCase)
            % READ_TESTFILE reads the results from PowerShell and Python3 into MATLAB.
            testCase.file_hashes = jsondecode(fileread(testCase.RESULTS_FILE));
        end
    end

    methods(Test)
        function test_filereadout(testCase)
            % TEST_FILEREADOUT will call the MEX API and confirm we get the correct
            % checksums.

            for algIdx = 1:numel(testCase.ALGORITHMS)
                hash = mfilehash(testCase.TEST_FILE, testCase.ALGORITHMS{algIdx});
                testCase.verifyTrue(strcmpi(hash, testCase.file_hashes.(testCase.ALGORITHMS{algIdx})), ...
                    sprintf('Unable to verify hash for algorithm "%s".',testCase.ALGORITHMS{algIdx}));
            end
        end
    end
    
end

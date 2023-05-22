classdef test_filehash < matlab.unittest.TestCase
    properties(Constant)
        ALGORITHMS = {'SHA1', 'SHA256', 'MD5', 'CRC32'};
        PS_PRINTF = 'Get-FileHash %s -Algorithm %s';
        TEST_FILE = fullfile(fileparts(mfilename('fullpath')), 'test', 'test.txt');
        RESULTS_FILE = fullfile(fileparts(mfilename('fullpath')), 'test', 'results.json');
    end

    properties
        file_hashes struct
    end


    methods(TestClassSetup)
        function read_testfile(testCase)
            % READ_TESTFILE reads the results from PowerShell and Python3 into MATLAB.
            testCase.file_hashes = jsondecode(testCase.RESULTS_FILE);
        end
    end

    methods(Test)
        function test_filereadout(testCase)
        end
    end
    
end
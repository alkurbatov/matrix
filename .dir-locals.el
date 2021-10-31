((c++-mode
  (flycheck-cppcheck-standards      . "c++14")
  (flycheck-clang-language-standard . "c++14")
  (flycheck-gcc-language-standard   . "c++14")
  (eval progn (let
                  ((local-include-paths
                    (list (concat (projectile-project-root) "src")
                          "/opt/local/include")))
                (setq flycheck-clang-include-path local-include-paths)
                (setq flycheck-gcc-include-path local-include-paths)))))

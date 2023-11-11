from setuptools import find_packages, setup

version = "0.0.1"

# Please update tox.ini when modifying dependency version requirements
install_requires = []

dev_extras = [
    "mypy",
    "pre-commit",
    "pytest",
    "types-PyYAML",
    "nose",
    "pep8",
    "tox",
    "pypandoc",
]

docs_extras = [
    "Sphinx>=1.0",  # autodoc_member_order = 'bysource', autodoc_default_flags
    "sphinx_rtd_theme",
    "sphinxcontrib-programoutput",
]

try:
    import pypandoc

    long_description = pypandoc.convert_file("README.md", "rst")
    long_description = long_description.replace("\r", "")

except (IOError, ImportError):
    import io

    with io.open("README.md", encoding="utf-8") as f:
        long_description = f.read()

setup(
    name="ph4-gas",
    version=version,
    description="Ph4 Sensirion Gas Index algorithm in Python ",
    long_description=long_description,
    url="https://github.com/ph4r05/ph4-sensirion-gas-index-algorithm-py",
    author="Dusan Klinec",
    author_email="dusan.klinec@gmail.com",
    license="MIT",
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Intended Audience :: Developers",
        "Programming Language :: Python",
        "Programming Language :: Python :: 2",
        "Programming Language :: Python :: 2.6",
        "Programming Language :: Python :: 2.7",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.3",
        "Programming Language :: Python :: 3.4",
        "Programming Language :: Python :: 3.5",
    ],
    packages=find_packages(),
    include_package_data=True,
    install_requires=install_requires,
    extras_require={
        "dev": dev_extras,
        "docs": docs_extras,
    },
)

\name{rLSwriteNodeSolutionFile}
\alias{rLSwriteNodeSolutionFile}

\title{Write the node solution to a file.}

\description{
 R interface function for LINDO API function \code{LSwriteNodeSolutionFile}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSwriteNodeSolutionFile(model,jScenario,iStage,pszFname)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{The scenario number the node belongs to.}
 \item{iStage}{The stage the node belongs to.}
 \item{pszFname}{Path and name of the file.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

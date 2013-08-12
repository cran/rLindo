\name{rLSwriteScenarioMPSFile}
\alias{rLSwriteScenarioMPSFile}

\title{Write scenario model in MPS format.}

\description{
 R interface function for LINDO API function \code{LSwriteScenarioMPSFile}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSwriteScenarioMPSFile(model,jScenario,pszFname,nFormat)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{The scenario to write in MPS format.}
 \item{pszFname}{Path and name of the MPS file.}
 \item{nFormat}{An integer parameter indicating whether the MPS file is formatted or not. Possible values are:
                   \itemize{
                        \item{LS_FORMATTED_MPS}
                        \item{LS_UNFORMATTED_MPS}
                        \item{LS_FORMATTED_MPS_COMP}
                   }
                }
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
